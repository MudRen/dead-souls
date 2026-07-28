/*  Allows players to possibly backstab a targets
 *  created by Rush@Dead Souls
 *  Version: @(#) backstab.c 1.3@(#)
 *  Last Modified: 96/12/21
 */

#include <lib.h>
#include <position.h>
#include "damage_types.h"
#include "include/backstab.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("backstab");
    SetRules("LIV");
    SetErrorMessage("你想暗算谁？");
    SetHelp("Syntax: backstab <LIVING>\n\n"
            "This sneaky attack allows more devious players to "
            "backstab a specified target.");
}

mixed can_backstab_liv() {
    if( !environment(this_player()) ) return 0;
    if( this_player()->GetInCombat() )
        return "你正在战斗中，无法分心！";
    else return this_player()->CanManipulate();
}

mixed do_backstab_liv(object ob) {
    object env;

    if(!(env = environment(this_player()))) return 0;
    if( this_player()->GetPosition() != POSITION_STANDING )
        this_player()->eventStand();   
    if(!ob || !present(ob, env)) {
        this_player()->eventPrint("你的受害者已经不在这里了。");
        return 1;
    }
    this_player()->RemoveNonTargets(({ob}));
    this_player()->eventPrint("%^RED%^你悄悄绕到" +
            ob->GetName() + "身后...%^RESET%^");
    this_player()->SetAttack(ob, (:eventBackstab, this_player(), ob:));
    return 1;
}

int eventBackstab(object backstabber, object target) {
    object env;
    float tmp;
    int suprise;
    object *weapons;
    int numberOfWeapons;
    int numberOfStabs;
    int i;

    if(!backstabber || !(env = environment(backstabber))) return 0;
    if(!target || !present(target, env)) {
        backstabber->eventPrint("你的受害者已经不在这里了。");
        return 1;
    }

    tmp = backstabber->GetSkillLevel("stealth")*1.5;
    tmp += backstabber->GetStatLevel("charisma")/2.0;
    tmp += backstabber->GetStatLevel("luck")/3.0;
    tmp += backstabber->GetMobility()/3.0;
    tmp -= target->GetStatLevel("luck")/3.0;
    tmp -= target->GetStatLevel("wisdom")/3.0;
    tmp -= target->GetMobility()/5.0;
    tmp *= 1.0;
    if(tmp < 1.0) tmp = 1.0;
    suprise = to_int(tmp);

    backstabber->AddSkillPoints("stealth", to_int(suprise * 3.0));
    backstabber->AddStaminaPoints(-(5 + random(5)));
    moral_act(backstabber, target, -30);

    if(suprise < random(100) || !present(target, environment(backstabber))) {
        backstabber->eventPrint("%^RED%^" + target->GetName()
                + "闪开了你笨拙的暗杀。%^RESET%^");
        target->eventPrint("%^RED%^你轻松闪开了" + possessive_noun(backstabber)
                + "暗杀企图。%^RESET%^");
        environment(backstabber)->eventPrint("%^RED%^" + target->GetName()
                + "闪开了" + possessive_noun(backstabber) + "暗杀企图。%^RESET%^",
                ({backstabber, target}));
        return 1;
    }  

    weapons = backstabber->GetWielded();
    numberOfWeapons = sizeof(weapons);

    if(!numberOfWeapons) {
        backstabber->eventPrint("%^RED%^你徒劳地用双拳捶打"
                + possessive_noun(target) + "背部。%^RESET%^");
        target->eventPrint("%^RED%^有人在你的背上徒劳地捶打着。%^RESET%^");
        environment(backstabber)->eventPrint("%^RED%^" + backstabber->GetName()
                + "熟练地暗算" + target->GetName() + "……不幸的是"
                + nominative(backstabber) + "忘了带刀。%^RESET%^",
                ({backstabber, target}));
        return 1;
    }

    numberOfStabs = 0;
    for(i = 0; i < numberOfWeapons && target; i++)
        numberOfStabs += eventStab(backstabber, target, weapons[i]);
    if(!numberOfStabs) {
        target->eventPrint("%^RED%^你闪开了" + possessive_noun(backstabber)
                + "暗杀企图。%^RESET%^");
        return 1;
    }

    backstabber->eventExecuteAttack(target);
    return 1;
}

int eventStab(object backstabber, object target, object weapon) {
    string weaponType;
    int damage;
    float x;
    int percentDamage;
    float adjustment;
    int numberWielded;

    if(!(weaponType = weapon->GetWeaponType())) return 0;
    numberWielded = sizeof(backstabber->GetWielded());

    x = weapon->GetClass() * 5.0;
    x += backstabber->GetSkillLevel(weaponType + " attack")/1.0;
    x += backstabber->GetStatLevel("strength")/2.0;
    x += backstabber->GetStatLevel("luck")/3.0;
    x += backstabber->GetMobility()/3.0;
    if(numberWielded > 1) {
        adjustment = backstabber->GetSkillLevel("multi-weapon") / (numberWielded / 2.0);
        x *= adjustment/100.0;
    }
    x -= target->GetStatLevel("luck")/3.0;
    x *= 0.5;
    x = (x + random(x)) / 2.0;
    if(weaponType != "knife") x = (x - 50.0) / 4.0;
    if(x < 1.0) x = 0.0;

    damage = target->eventReceiveDamage(backstabber,
            weapon->GetDamageType(), to_int(x), 0, target->GetTorso());
    if(damage > 0) {
        weapon->eventReceiveDamage(BLUNT, damage, 0, target->GetTorso());
        percentDamage = damage * 100 / target->GetMaxHealthPoints();
        if(percentDamage < 1) percentDamage = 0;
    }
    else percentDamage = 0;
    eventPrintDamage(backstabber, target, weapon, percentDamage);
    backstabber->AddSkillPoints(weaponType + " attack", 7 + damage/10);
    return 1;
}

int eventPrintDamage(object backstabber, object target, object weapon, int percentDamage) {
    string adverb;
    string myVerb;
    string verb;

    if(!percentDamage) {
        backstabber->eventPrint("%^RED%^你笨拙地摆弄着你的"
                + strip_article(weapon->GetShort()) + "。%^RESET%^");
        environment(backstabber)->eventPrint("%^RED%^" + backstabber->GetName()
                + "笨拙地摆弄着" + possessive(backstabber) + " "
                + strip_article(weapon->GetShort()) + ".%^RESET%^",
                ({backstabber, target}));
        return 1;
    }

    if(percentDamage < 15) {
        myVerb = "猛刺 ";
        verb = "猛刺 ";
        adverb = "犀利地 ";
    }
    else if(percentDamage < 30) {
        myVerb = "刺入 ";
        verb = "刺入 ";
        adverb = "痛苦地 ";
    }
    else {
        myVerb = "深刺 ";
        verb = "深刺 ";
        adverb = "深深地 ";
    }

    backstabber->eventPrint("%^RED%^你" + myVerb + "你的"
            + strip_article(weapon->GetShort()) + " " + adverb + "刺入"
            + possessive_noun(target) + "的背部。%^RESET%^");
    target->eventPrint("%^RED%^你的背部感到灼烧般的剧痛，一把" + weapon->GetWeaponType()
            + " " + verb + adverb + "刺入了你的身体。%^RESET%^");
    environment(backstabber)->eventPrint("%^RED%^" + backstabber->GetName() + " "
            + verb + possessive(backstabber) + " " + strip_article(weapon->GetShort())
            + " " + adverb + "刺入" + possessive_noun(target) + "背部。%^RESET%^",
            ({backstabber, target}));

    return 1;
}
