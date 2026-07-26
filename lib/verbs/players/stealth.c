/*  /verbs/players/stealth.c
 *  by BillGates 961109
 *  allows players to move silently from room to room
 */

#include <lib.h>
#include "include/stealth.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("stealth");
    SetRules("","WRD");
    SetHelp("用法：stealth [on | off]\n\n"
            "如果潜行是你可用的技能，此命令可以开启或关闭潜行状态。");
}

mixed can_stealth() {
    return this_player()->CanCastMagic(0, "stealth");
}

mixed can_stealth_wrd() {
    return can_stealth();
}

mixed do_stealth() {
    return do_stealth_wrd("");
}

mixed do_stealth_wrd(string args) {
    object caster  = this_player();
    object env = environment(caster);

    int skill = this_agent()->GetSkillLevel("stealth");
    if( skill < 20 ) {
        caster->eventPrint("你还不够狡猾。");
        return 1;
    }


    if( args == "on" ) {
        if( caster->GetStaminaPoints() < 50 ) {
            caster->eventPrint("你太累了，无法安静地移动。",env);
            env->eventPrint(caster->GetName() + "看起来很疲惫。",caster);
            return 0;
        }


        if( caster->GetInCombat() ) {
            caster->eventPrint("你现在正忙着战斗呢。",env);
            return 0;
        }
    }	    
    eventStealth(caster, args, skill);
    return 1;
}


int eventStealth(object caster, string args, int skill) {

    if( !(caster) ) return 0;

    if( !environment(caster) ) {
        caster->eventPrint("你不在任何地方。");
        return 0;
    }

    if(args == "") {
        if(caster->GetProperty("stealthy")) {
            caster->eventPrint("你目前正在安静地移动。");
        }
        else caster->eventPrint("你像往常一样吵闹地移动。");
        return 1;
    }

    if(args == "on") {
        if(caster->GetProperty("stealthy")) {
            caster->eventPrint("你已经在安静地移动了！");
            return 0;
        }
        caster->SetProperty("stealthy",1);
        caster->eventPrint("%^RED%^你开始潜行。");
        caster->AdStaminaPoints(-30 - random(40));
        caster->AddSkillPoints("stealth",skill*skill/8);
        return 1;
    }

    if(args == "off") {
        if(caster->GetProperty("stealthy")) {
            caster->SetProperty("stealthy",0);
            caster->eventPrint("%^BOLD%^%^CYAN%^你停止了潜行。",
                    environment(caster));
            return 1;
        }
        else caster->eventPrint("你目前没有在潜行！");
        return 0;
    }  		     

    return 1;
}
