/*    /verbs/items/steal.c
 *    from the Dead Souls Mud Library
 *    steal WRD from LIV
 *    steal OBJ from LIV
 *    created by Descartes of Borg 951218
 */



#include <lib.h>
#include <rounds.h>
#include "include/steal.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("steal");
    SetRules("OBJ from LIV", "WRD from LIV", "OBS from LIV");
    SetErrorMessage("偷什么？从谁那里偷？");
    SetHelp("语法：<steal money from 生物>\n"
            "        <steal 物品 from 生物>\n"
            "        <steal all [of 物品] from 生物>\n\n"
            "使用你的偷窃技能来窃取他人的物品或金钱。"
            "偷物品比偷钱困难得多，试图一次偷取"
            "多个物品是危险的。");
}

mixed can_steal_wrd_from_liv(string wrd) {
    if( wrd != "money" ) return 0;
    if( this_player()->GetSkillLevel("stealing") < 1 )
        return "你的偷窃技能不够熟练。";
    if( environment(this_player())->GetProperty("no steal") )
        return "神秘的力量阻止了你的偷窃行为。";
    if( this_player()->GetStaminaPoints() < 10 )
        return "你太累了，无法进行这种鬼祟的活动。";
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed can_steal_obj_from_liv() {
    if( this_player()->GetSkillLevel("stealing") < 1 )
        return "你的偷窃技能不够熟练。";
    if( environment(this_player())->GetProperty("no steal") )
        return "神秘的力量阻止了你的偷窃行为。";
    if( this_player()->GetStaminaPoints() < 20 )
        return "你太累了，无法进行这种鬼祟的活动。";
    if(intp(check_light())) return this_player()->CanManipulate();
    else return check_light();
}

mixed do_steal_wrd_from_liv(string wrd, object liv) {
    this_player()->eventPrint("你盯着" + liv->GetName() +
            "，心中盘算着" + possessive(liv) +
            "口袋里的东西。");
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventSteal,this_player(), "money", liv :),
                ROUND_OTHER);
    else eventSteal(this_player(), "money", liv);
    return 1;
}

mixed do_steal_obj_from_liv(object item, object liv) {
    if(!item) return "这里没有那个。";
    if( environment(item) != liv ) {
        this_player()->eventPrint(liv->GetName() + "没有那个东西。");
        return 1;
    }
    if(item->GetProperty("no steal")){
        this_player()->eventPrint("那个物品无法被偷取。");
        return 1;
    }
    this_player()->eventPrint("你盯着" + liv->GetName() +
            "，心中盘算着" + possessive(liv) + "的" +
            remove_article(item->GetShort()) + "。");
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventSteal, this_player(), ({ item }),
                    liv :), ROUND_OTHER);
    else eventSteal(this_player(), ({ item }), liv);
    return 1;
}

mixed do_steal_obs_from_liv(mixed *res, object liv) {
    object *obs;

    obs = filter(res, (: objectp :));
    if( !sizeof(obs) ) {
        mixed *ua;

        ua = unique_array(res, (: $1 :));
        foreach(mixed *lines in ua) this_player()->eventPrint(lines[0]);
        return 1;
    }

    foreach(mixed thing in res){
        if(objectp(thing) && thing->GetProperty("no steal")){
            this_player()->eventPrint("其中一个物品无法被偷取，导致"+
                    "你无法集中注意力去偷取其他物品。");
            return 1;
        }
    }
    this_player()->eventPrint("你盯着" + liv->GetName() +
            "，心中盘算着" + possessive(liv) +
            "的财物。");
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0, (: eventSteal, this_player(), obs, liv :),
                ROUND_OTHER);
    else eventSteal(this_player(), obs, liv);
    return 1;
}

protected void eventSteal(object who, mixed what, object target) {
    if(objectp(what) && what->GetProperty("no steal")){
        write("那个物品无法被偷取。");
        return;
    }
    who->eventSteal(who, what, target);
}
