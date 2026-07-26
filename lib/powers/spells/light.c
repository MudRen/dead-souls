#include <lib.h>
#include <magic.h>
#include <damage_types.h>
#include <magic_protection.h>

inherit LIB_SPELL;

protected void create() {
    spell::create();
    SetSpell("light");
    SetRules("", "LIV");
    SetSpellType(SPELL_OTHER);
    SetRequiredMagic(20);
    SetSkills(([ "conjuring" : 5 ]));
    SetMagicCost(20, 0);
    SetDifficulty(1);
    SetMorality(10);
    SetHelp("语法: cast light\n"
            "在你周围产生放射光芒，让你在黑暗中也能看见。");
}

int eventCast(object who, int level) {
    int intel = who->GetStatLevel("intelligence");
    int duration = intel + who->GetSkillLevel("conjuring") + who->GetSpellLevel("light");
    object mojo = new("/obj/light");

    duration += (who->GetLevel());
    duration *= 5;
    mojo->SetDuration(duration);
    mojo->eventMove(who);

    send_messages("", "一个%^B_BLACK%^%^BOLD%^YELLOW%^魔法光芒%^RESET%^"
            "出现在$agent_possessive_noun的周围。", who, 0,
            environment(who));
    return 1;
}
