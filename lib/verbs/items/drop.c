/*    /verbs/items/drop.c
 *    from the Dead Souls Mud Library
 *    drop OBJ
 *    drop OBS
 *    drop WRD WRD
 *    created by Descartes of Borg 960113
 */



#include <lib.h>
#include "include/drop.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("drop");
    SetSynonyms("put down");
    SetRules("OBS", "WRD WRD");
    SetErrorMessage("丢弃什么？");
    SetHelp("用法：drop <物品>\n"
            "      drop all\n"
            "      drop all <物品类型>\n"
            "      drop <数量> <货币>\n\n"
            "允许你丢弃你拥有的物品，或丢弃你携带的一定数量的货币。\n\n"
            "另见：get, put");
}

mixed can_drop_obj(object ob) { return this_player()->CanManipulate(); }

//mixed can_drop_wrd_wrd(string num, string curr) {
mixed can_drop_wrd_wrd(mixed args...) {
    string num, curr;
    int amt;
    object ob;

    num = args[0];
    curr = args[1];

    ob = get_object(num+" "+curr);

    if(ob) return can_drop_obj(ob);

    if( !num || !curr ) return 0;
    if( (amt = to_int(num)) < 1 ) return "你不能那样做！";
    if( this_player()->GetCurrency(curr) < amt )
        return "你没有那么多" + curr + "。";
    if(newbiep(this_player())) return "新手不能丢弃金钱。";
    return this_player()->CanManipulate();
}

mixed do_drop_obj(object ob) {
    return ob->eventDrop(this_player());
}

mixed do_drop_obs(mixed *res) {
    object *obs, *eligible;
    mixed tmp;

    if( !sizeof(res) ) {
        this_player()->eventPrint("你没有东西可以丢弃！");
        return 1;
    }
    obs = filter(res, (: objectp :));
    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(res, (: $1 :));
        foreach(string *list in ua) this_player()->eventPrint(list[0]);
        return 1;
    }
    eligible=filter(obs, (: (!($1->GetWorn()) && environment($1) == this_player()) :));
    if(!sizeof(eligible)){
        write("请先卸下或解除装备再尝试丢弃。");
        eligible = ({});
        return 1;
    }
    foreach(object ob in eligible)
        if( (tmp = ob->eventDrop(this_player())) != 1 ) {
            if( stringp(tmp) ) this_player()->eventPrint(tmp);
            else this_player()->eventPrint("你无法丢弃" +
                    ob->GetShort() + "。");
        }
    return 1;
}

//mixed do_drop_wrd_wrd(string num, string curr) {
mixed do_drop_wrd_wrd(mixed args...) {
    object ob, pile, env;
    string num, curr;
    int amt;

    num = args[0];
    curr = args[1];

    if(ob = get_object(num+" "+curr)) return do_drop_obj(ob);

    amt = to_int(num);
    env = environment(this_player());
    pile = new(LIB_PILE);
    pile->SetPile(curr, amt);
    if( !(pile->eventMove(env)) ||
            this_player()->AddCurrency(curr, -amt) == -1 ) {
        this_player()->eventPrint("某些事情阻碍了你的行动。");
        pile->eventDestruct();
        return 1;
    }
    this_player()->eventPrint("你丢弃了" + amt + "个" + curr + "。");
    environment(this_player())->eventPrint(this_player()->GetName() +
            "丢弃了一些" + curr + "。",
            this_player());
    return 1;
}
