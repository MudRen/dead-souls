/*  /verbs/spells/judge.c
 *  a skill for players to judge the relative worth of items
 *  created 961120 by Bill Gates@Dead Souls
 */

#include <lib.h>
#include <vendor_types.h>
#include <rounds.h>
#include "include/judge.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("judge");
    SetSynonyms("equate");
    SetRules("OBJ to OBJ");
    SetErrorMessage("你想比较哪两样东西？");
    SetHelp("Syntax: equate OBJ to OBJ\n\n"
            "A bargaining ability which allows people to compare the "
            "relative worth of two items.  The more experienced you are "
            "at bartering, the better chance you have of correctly judging "
            "the more valuable item.\n\n"
            "See help: item commands");
}

mixed can_judge_obj_to_obj() {
    if( this_player()->GetLevel() < 6 ) {
        this_player()->eventPrint("你的经验不足以判断"
                "物品的价值。");
        return 0;
    }
    return this_player()->CanCastMagic(1, "judge");
}


mixed do_judge_obj_to_obj(object obj1, object obj2) {
    int level;
    string name1, name2;
    object caster = this_player();
    if( !(caster->GetSkillLevel("bargaining")) ) {
        return "你没有判断物品的技能。"; }
    if (!obj1 || !obj2) return "你必须拿一样东西和另一样比较。";
    if (obj1 == obj2) return "那倒很有用呢！";

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

    level = caster->GetSkillLevel("bargaining");
    caster->eventPrint("你专注地凝视着" +name1+"和" +name2+"。");
    environment(caster)->eventPrint( caster->GetName() +
            "专心致志地比较着" + name1 + "和" + name2 + "。", caster);
    if( this_player()->GetInCombat() )
        this_player()->SetAttack(0,
                (: eventJudge, this_player(), obj1, obj2, level :),
                ROUND_OTHER);
    else eventJudge(this_player(), obj1, obj2, level);
    return 1;
}


int eventJudge(object caster, object obj1, object obj2, int level) {

    int obj1lvl, obj2lvl;
    string better;

    int cost = random(50) + 50;

    if( !(obj1 && obj2) ) return 0;
    if( (environment(obj1) != caster) || (environment(obj2) != caster) ) {
        caster->eventPrint("你必须同时拥有两样物品才能比较。");
        return 0;
    }
    if( cost > caster->GetStaminaPoints() ) {
        caster->eventPrint("你现在太累了，无法判断。");
        environment(caster)->eventPrint(
                caster->GetName() + "看起来很累。", caster);
        return 0;

    }
    caster->AddStaminaPoints(-cost);
    obj1lvl = obj1->GetValue();
    obj2lvl = obj2->GetValue();

    if( level < (5 + random(35))) {

        if(random(7)) {
            if(random(5) < 2) {
                better = obj2->GetShort();
            }
            else better = obj1->GetShort();
            caster->eventPrint("%^BOLD%^%^WHITE%^"
                    "你判断出" + better + "%^BOLD%^%^WHITE%^"
                    "是更有价值的物品。%^RESET%^");
            return 0;
        }
        else caster->eventPrint("%^BOLD%^%^WHITE%^"
                "你判断出这两样物品价值相等。"
                ".%^RESET%^");
        caster->AddSkillPoints("bargaining",random(25));
        return 1;
    }
    /* Return the right answer */
    if(obj1lvl == obj2lvl) {
        caster->eventPrint("%^BOLD%^%^WHITE%^"
                "你判断出这两样物品价值相等。"
                ".%^RESET%^");
        return 1;
    }
    if(obj1lvl > obj2lvl) {
        better = obj1->GetShort();
    }
    else better = obj2->GetShort();
    caster->eventPrint("%^BOLD%^%^WHITE%^"
            "你判断出" + better + "%^BOLD%^%^WHITE%^"
            "是更有价值的物品。%^RESET%^");
    caster->AddSkillPoints("bargaining",random(50));
    return 1;

}
