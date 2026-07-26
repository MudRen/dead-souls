/*    /spells/missile.c
 *    From Dead Souls LPMud
 *    Created by Descartes of Borg 961028
 *    Version: %A$
 *    Last modified: 96/11/02
 */

#include <lib.h>
#include <magic.h>
#include <damage_types.h>

inherit LIB_SPELL;

protected void create() {
    spell::create();
    SetSpell("missile");
    SetRules("", "LIV");
    SetSpellType(SPELL_COMBAT);
    SetRequiredMagic(5);
    SetSkills(([ "conjuring" : 0, "magic attack" : 0 ]));
    SetMagicCost(10, 3);
    SetStaminaCost(5, 3);
    SetDifficulty(0);
    SetMorality(-1);
    SetAutoDamage(3);
    SetDamage(MAGIC|BLUNT, ({15, 6}) );
    SetMessages(({ ({ "are", "$target_name在$agent_possessive"
                    "的魔法飞弹攻击下毫发无伤。" }),
                ({ "stings", "$agent_possessive_noun的飞弹"
                 "刺痛了$target_name。" }),
                ({ "slams", "$agent_possessive_noun的飞弹"
                 "猛击了$target_name。" }) }));
    SetHelp("语法: <cast missile>\n"
            "        <cast missile on LIVING>\n\n"
            "这个法术凭空召唤出一枚魔法飞弹，"
            "将其射向指定的敌人。"
            "如果在战斗中没有指定目标，"
            "飞弹将自动攻击你当前的敌人。");
}
