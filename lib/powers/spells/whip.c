#include <lib.h>
#include <magic.h>
#include <damage_types.h>

inherit LIB_SPELL;

protected void create() {
    spell::create();
    SetSpell("whip");
    SetRules("");
    SetSpellType(SPELL_OTHER);
    SetRequiredMagic(5);
    SetSkills(([ "conjuring" : 0 ]));
    SetMagicCost(50, 50);
    SetStaminaCost(10, 10);
    SetDifficulty(0);
    SetHelp("语法: <cast whip>\n\n"
            "这个法术召唤一条由魔法能量构成的鞭子，"
            "并将其移动到可用的肢体上。如果解除武器，它将消失。"
            "鞭子作为武器的威力取决于你的施法能力。");
}

varargs int eventCast(object who, int level, string limb, object* targs){
    object whip;
    object *limbs = this_player()->GetWieldingLimbs();
    object *whips = filter(all_inventory(this_player()),
            (: base_name($1) == "/obj/whip" :) );
    if(sizeof(whips)){
        write("你已经有一条能量鞭了。");
        return 1;
    }
    whip = new("/obj/whip");
    write("你用力挥动手臂，召唤出一条能量鞭！");
    say(this_player()->GetName()+"用力挥动"+
            possessive(this_player())+"手臂，召唤出一条能量鞭！");
    whip->eventMove(this_player());
    limbs = filter(limbs, (: !(this_player()->GetWielded($1)) :) );
    if(sizeof(limbs)){
        int weapclass = (this_player()->GetLevel());
        weapclass += (this_player()->GetStatLevel("intelligence") / 4);
        weapclass += (this_player()->GetSpellLevel("whip") / 10);
        weapclass += (this_player()->GetSkillLevel("magic attack") / 3);
        weapclass += (this_player()->GetSkillLevel("conjuring") / 3);
        whip->eventEquip(this_player(),limbs[0]);
        whip->SetClass(weapclass);
        whip->SetDuration(this_player()->GetSkillLevel("conjuring") * 20);
    }
    return 1;
}

