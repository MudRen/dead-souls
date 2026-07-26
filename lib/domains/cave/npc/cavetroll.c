#include <lib.h>
#include <damage_types.h>
#include <size_types.h>

inherit LIB_NPC;

protected void create() {
    npc::create();
    SetKeyName("troll");
    SetId(({"cavetroll"}));
    SetAdjectives(({"dirty","cave"}));
    SetShort("一只洞穴巨魔");
    SetLong("与那些更文明的同类不同，洞穴巨魔是一种巨大而力量恐怖的生物，性情更加凶残。它岩石般的皮肤使它难以受伤，而它庞大的肌肉使与之战斗的人难以生还。");
    SetInventory(([
                "/domains/cave/armor/loincloth" : "wear loincloth",
                ]));
    SetLevel(13);
    SetRace("troll");
    SetClass("fighter");
    SetGender("male");
    SetMelee(1);
    SetSkill("melee attack",50,50,10);
    SetStat("strength",90,1);
    SetStat("agility",50,1);
    SetResistance(BLADE,"high");
    SetResistance(KNIFE,"high");
    SetResistance(PIERCE,"high");
    SetResistance(BITE,"high");
    SetEncounter(100);
    SetSize(S_LARGE);
}

void init(){
    ::init();
}
