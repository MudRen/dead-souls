/*  /verbs/spells/judge.c
 *  a skill for players to judge the relative weight of items
 *  created 96/12/04 by Faldir@Dead Souls
 */

#include <lib.h>
#include <vendor_types.h>
#include <rounds.h>
#include "include/balance.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("balance");
    SetRules("OBJ to OBJ");
    SetErrorMessage("你想比较哪两样东西？");
    SetHelp("Syntax: balance OBJ to OBJ\n\n"
            "A simple tool for determining which is the heavier of two objects."
            "See help: item commands");
}

mixed can_balance_obj_to_obj() {
    return this_player()->CanCastMagic(1, "balance");
}


mixed do_balance_obj_to_obj(object obj1, object obj2) {
    string name1, name2;
    object caster = this_player();
    if(!obj1 || !obj2) return "你必须拿一样东西和另一样比较。";
    if(obj1 == obj2) return "那倒很有用呢！";
    /* Check for presence of objects */
    name1 = obj1->GetShort();
    name2 = obj2->GetShort();

    if( environment(obj1) != caster ) {
        caster->eventPrint("你没有" +name1+"。");
        return 1;
    }

    if( environment(obj2) != caster ) {
        caster->eventPrint("你没有" +name2+"。");
        return 1;
    }

    caster->eventPrint("你专注地凝视着" +name1+"和" +name2+"。");
    environment(caster)->eventPrint( caster->GetName() +
            "专心致志地比较着" + name1 + "和" + name2 + "。", caster);
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0,
                (: eventBalance, this_player(), obj1, obj2 :),
                ROUND_OTHER);
    else eventBalance(this_player(), obj1, obj2);
    return 1;
}


int eventBalance(object caster, object obj1, object obj2) {

    int obj1lvl, obj2lvl;
    string better;

    int cost = random(50) + 50;

    if( !(obj1 && obj2) ) return 0;
    if( (environment(obj1) != caster) || (environment(obj2) != caster) ) {
        caster->eventPrint("你必须同时拥有两样物品才能比较。");
        return 0;
    }
    if( cost > caster->GetStaminaPoints() ) {
        caster->eventPrint("你现在太累了，无法称量。");
        environment(caster)->eventPrint(
                caster->GetName() + "看起来很累。", caster);
        return 0;

    }
    caster->AddStaminaPoints(-cost);
    obj1lvl = obj1->GetMass();
    obj2lvl = obj2->GetMass();

    /* Return the right answer */
    if(obj1lvl == obj2lvl) {
        caster->eventPrint("%^BOLD%^%^WHITE%^"
                "你判断出这两样物品重量相等。"
                ".%^RESET%^");
        return 1;
    }
    if(obj1lvl > obj2lvl) {
        better = obj1->GetShort();
    }
    else better = obj2->GetShort();
    caster->eventPrint("%^BOLD%^%^WHITE%^"
            "你判断出" + better + "%^BOLD%^%^WHITE%^"
            "是更重的物品。%^RESET%^");
    return 1;

} 
