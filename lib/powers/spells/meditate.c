#include <lib.h>
#include <magic.h>
#include <damage_types.h>
#include <magic_protection.h>

inherit LIB_SPELL;

protected void create() {
    spell::create();
    SetSpell("meditate");
    SetRules("", "LIV");
    SetSpellType(SPELL_DEFENSE);
    SetRequiredMagic(50);
    SetSkills(([ "magic defense" : 0 ]));
    SetMagicCost(150, 100);
    SetDifficulty(1);
    SetMorality(10);
    SetHelp("语法: <cast meditate>\n"
            "一个能让施法者更快恢复耐力的法术。\n\n");
}

int eventCast(object who, int level) {
    int wis, skill, stamina_level;
    object mojo = new("/secure/obj/meditate_mojo");
    wis = who->GetStatLevel("wisdom");
    skill = who->GetSkillLevel("magic defense");
    stamina_level = level;
    stamina_level *= (random(skill/10) + 1);
    stamina_level += random(wis/2);
    stamina_level += 10;

    who->AddStaminaPoints(stamina_level);
    mojo->AddDuration(who->GetSkillLevel("conjuring") + who->GetSpellLevel("meditate"));
    mojo->eventMove(who);

    send_messages("", "一个%^BOLD%^MAGENTA%^暗黑魔法力场%^RESET%^"
            "短暂地出现在$agent_possessive_noun的周围。", who, 0,
            environment(who));
    return 1;
}

