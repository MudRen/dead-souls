/*    /verbs/items/give.c
 *    from the Dead Souls Mud Library
 *    give LIV OBJ
 *    give OBJ to LIV
 *    give LIV WRD WRD
 *    give WRD WRD to LIV
 *    created by Descartes of Borg 950113
 */

#include <lib.h>
#include "include/give.h"

inherit LIB_VERB;

string curr2;

protected void create() {
    verb::create();
    SetVerb("give");
    SetRules("LIV WRD WRD", "WRD WRD to LIV", "OBS LIV", "LIV OBS", "OBS to LIV" );
    SetErrorMessage("给谁什么东西？");
    SetHelp("用法：give <生物> <物品>\n"
            "      give <生物> <物品们>\n"
            "      give <物品> to <生物>\n"
            "      give <物品们> to <生物>\n"
            "      give <生物> <数量> <货币>\n"
            "      give <数量> <货币> to <生物>\n\n"
            "此命令允许你将你拥有的东西交给其他人。\n\n"
            "另见：drop, get, put");
}

mixed can_give_liv_obj(mixed args...) {
    return can_give_obj_to_liv();
}

mixed can_give_obj_liv(mixed args...) {
    return can_give_obj_to_liv();
}

mixed can_give_obj_to_liv(mixed args...) { 
    return this_player()->CanManipulate(); }

    mixed can_give_liv_wrd_wrd(object targ, string num, string curr) {
        return can_give_wrd_wrd_to_liv(num, curr, targ);
    }

mixed can_give_wrd_wrd_to_liv(string num, string curr, object targ) {
    int amt;
    curr2 = curr;
    if(!valid_currency(curr)) curr = truncate(curr,1);
    if(!valid_currency(curr)) curr = truncate(curr,1);
    if(!valid_currency(curr)) curr = curr2 +"s";
    if(!valid_currency(curr)) curr = curr2 +"es";
    if(valid_currency(curr)) curr2 = curr;

    if(sscanf(num,"%d",amt) != 1){
        if(valid_currency(curr)) return "请用数字指定数量。";
        else return "那不是有效的货币。";
    }
    if( amt < 1 ) return "这是什么数量？";
    if( amt > this_player()->GetCurrency(lower_case(curr)) )
        return "你没有那么多" + curr + "。";
    if(newbiep(this_player())) return "新手不能赠送金钱。";
    return this_player()->CanManipulate();
}

//mixed do_give_liv_obj(object target, object what) {
mixed do_give_liv_obj(mixed args...) {
    object target, what;
    target = args[0];
    what = args[1];
    return do_give_obj_to_liv(what, target);
}

//mixed do_give_obj_liv(object what, object target) {
mixed do_give_obj_liv(mixed args...) {
    object target, what;
    target = args[1];
    what = args[0];
    return do_give_obj_to_liv(what, target);
}

//mixed do_give_obj_to_liv(object what, object target) {
mixed do_give_obj_to_liv(mixed args...) {
    object target, what;
    target = args[1];
    what = args[0];

    if(!intp(target->CanManipulate())){
        this_player()->eventPrint(target->GetName()+"没有能力"+
                "拿住那个。");
        return 1;
    }
    if( !(what->eventMove(target)) ) {
        this_player()->eventPrint("他们现在无法接受那个。");
        return 1;
    }
    this_player()->eventPrint("你把" + what->GetShort() + "给了" + target->GetName() + "。");
    target->eventPrint(this_player()->GetName() + "把" +
            what->GetShort() + "给了你。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "把" + what->GetShort() + "给了" +
            target->GetName() + "。",
            ({ this_player(), target }));
    return 1;
}

mixed do_give_liv_wrd_wrd(object target, string num, string curr) {
    return do_give_wrd_wrd_to_liv(num, curr, target);
}

mixed do_give_wrd_wrd_to_liv(string num, string curr, object target) {
    int amt;
    if(curr2) curr = curr2;
    amt = to_int(num);
    if( target->AddCurrency(curr, amt) == -1 ) {
        this_player()->eventPrint("你就是没法把那笔钱送出去。");
        return 1;
    }
    if( this_player()->AddCurrency(curr, -amt) == -1 ) {
        target->AddCurrency(curr, -amt);
        this_player()->eventPrint("你拥有的金钱数量出了问题。");
        return 1;
    }
    this_player()->eventPrint("你给了" + target->GetName() + " " +
            amt + "个" + curr + "。");
    target->eventPrint(this_player()->GetName() + "给了你" +
            amt + "个" + curr + "。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "给了" + target->GetName() + " " +
            amt + "个" + curr + "。",
            ({ target, this_player() }));
    return 1;
}

mixed do_give_liv_obs(object target, mixed *items) {
    return do_give_obs_to_liv(items, target);
}

mixed do_give_obs_liv(mixed *items, object target) {
    return do_give_obs_to_liv(items, target);
}

mixed do_give_obs_to_liv(mixed *items, object target) {
    object *obs, *eligible;

    if( sizeof(items) < 1 ) {
        this_player()->eventPrint("你没有东西可以赠送。");
        return 1;
    }

    obs = filter(items, (: objectp :));
    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(items, (: $1 :));
        foreach(string *list in ua) this_player()->eventPrint(list[0]);
        return 1;
    }
    eligible=filter(obs, (: (!($1->GetWorn()) && environment($1) == this_player()) :));
    if(!sizeof(eligible)){
        write("请先卸下或解除装备再尝试赠送。");
        eligible = ({});
        return 1;
    }

    foreach(object ob in eligible) do_give_obj_to_liv(ob, target);
    return 1;
}
