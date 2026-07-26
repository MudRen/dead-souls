/*    /spells/buffer.c
 *    From Dead Souls LPMud
 *    Created by Blitz
 *    Converted to new spell system by BillGates 961119
 *    Version: @(#) buffer.c 1.6@(#)
 *    Last modified: 96/11/10
 */

#include <lib.h>
#include <magic.h>
#include <damage_types.h>
#include <magic_protection.h>
#include <function.h>

inherit LIB_SPELL;

int hitCallback(object who, object agent, int x, class MagicProtection cl);
void endCallback(object who);

protected void create() {
    spell::create();
    SetSpell("buffer");
    SetRules("", "LIV");
    SetSpellType(SPELL_DEFENSE);
    SetRequiredMagic(50);
    SetSkills(([ "magic defense" : 1 ]));
    SetMagicCost(40, 40);
    SetDifficulty(1);
    SetMorality(10);
    SetHelp("语法: <cast buffer>\n"
            "       <cast buffer on LIV>\n\n"
            "一个魔法防御法术，能让施法者在目标生物周围创造一个发光的护盾。\n\n");
}

int eventCast(object who, int level, string race, object* targets) {
    class MagicProtection protection;
    class MagicProtection *Protections;
    object target = targets[0];
    int prot_level, skill, wis, maxprot;

    maxprot = (who->GetMaxHealthPoints()) / 2;

    Protections = target->GetMagicProtection();
    foreach(class MagicProtection tmp in Protections){
        if(!tmp->obname) continue;
        if(tmp->obname == file_name(this_object())){
            if(!(functionp(tmp->hit) & FP_OWNER_DESTED)){
                if(target == this_player()){
                    write("你已经被防护护盾保护了！");
                }
                else {
                    write("他们已经被防护护盾保护了！");
                }
                return 1;
            }
        }
    }

    wis = who->GetStatLevel("wisdom");
    skill = who->GetSkillLevel("magic defense");
    prot_level = level * 3;
    prot_level += (skill * 3);
    prot_level += (wis / 2);

    if(prot_level > maxprot) prot_level = maxprot;

    protection = new(class MagicProtection);
    protection->bits = ALL_EXTERNAL_DAMAGE;
    protection->caster = who;
    protection->absorb = prot_level;
    protection->args = level;
    protection->hit = (: hitCallback :);
    protection->end = (: endCallback :);
    protection->obname = file_name(this_object());
    protection->ob = this_object();
    protection->name = "magical buffer";
    target->AddMagicProtection(protection);
    if( target == who ) {
        send_messages("", "一个%^BOLD%^CYAN%^半透明的魔法护盾%^RESET%^"
                "突然出现在$agent_possessive_noun的周围。", who, 0,
                environment(target));
    }
    else {
        send_messages("", "一个%^BOLD%^CYAN%^半透明的魔法护盾%^RESET%^"
                "突然出现在$target_possessive_noun的周围。", who,
                target, environment(target));
    }
    return 1;
}

int hitCallback(object who, object agent, int x, class MagicProtection cl) {
    string str;
    object Caster = cl->caster;

    if( agent->GetUndead() ) return 0;
    str = agent->GetName() || agent->GetShort();
    if( who == Caster ) {
        who->eventTrainSkill("magic defense",cl->args,x,1);
    }
    else if( Caster && playerp(who) && Caster != who ) {
        Caster->eventTrainSkill("magic defense",cl->args,0,1);
    }

    send_messages("", "$agent_name周围的%^YELLOW%^魔法护盾%^RESET%^"
            "在$target_name的攻击下颤动。",
            who, agent, environment(who));
    return x;
}

void endCallback(object who) {
    if( who ) {
        send_messages("", "$agent_name周围的%^BOLD%^CYAN%^魔法护盾%^RESET%^"
                "碎裂消散了。", who, 0, environment(who));
    }
}
