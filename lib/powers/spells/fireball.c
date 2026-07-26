/*    /spells/fireball.c
 *    From Dead Souls LPMud
 *    Created by Descartes of Borg 961027
 *    Version: @(#) fireball.c 1.7@(#)
 *    Last modified: 96/11/02
 */

#include <lib.h>
#include <magic.h>
#include <damage_types.h>

inherit LIB_SPELL;

protected void create() {
    spell::create();
    SetSpell("fireball");
    SetRules("", "LIV");
    SetSpellType(SPELL_COMBAT);
    SetRequiredMagic(50);
    SetSkills(([ "conjuring" : 8, "magic attack" : 0 ]));
    SetMagicCost(30, 24);
    SetStaminaCost(20, 16);
    SetDifficulty(10);
    SetMorality(-20);
    SetAutoDamage(0);
    SetDamage(MAGIC|HEAT, ({ 20, 15 }) );
    SetMessages(({ ({ "accept", "$target_name微笑着接受了"
                    "$agent_possessive_noun的火球。" }),
                ({ "are", "$target_name被$agent_possessive_noun的"
                 "火球轻微烧焦了。" }),
                ({ "", "$agent_possessive_noun的"
                 "%^RED%^火球%^RESET%^"
                 "点燃了$target_name！" }),
                ({ "are", "$target_name被$agent_possessive_noun的"
                 "%^BOLD%^RED%^火球%^RESET%^烧成了灰烬。" }) }));
    SetHelp("语法: <cast fireball>\n"
            "        <cast fireball on LIVING>\n\n"
            "这个法术凭空召唤出一个巨大的火球，"
            "将其投向毫无防备的敌人。"
            "如果在战斗中没有指定目标，"
            "火球将自动攻击你当前的敌人。");
}
