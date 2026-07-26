#include <lib.h>

inherit "/domains/cave/etc/cave_orc";

int GetEnemyChaser() { return 1; }

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"armored","professional"}));
    SetShort("一个武装兽人");
    SetLong("这是一个非常高大的成年兽人，举止专业，目标明确。");
    SetInventory(([
                "/domains/cave/weap/axe" : "wield axe",
                "/domains/cave/weap/sword" : "wield sword",
                "/domains/cave/armor/leather_armor" : "wear leather armor",
                "/domains/cave/armor/orc_boot_l" : "wear left boot",
                "/domains/cave/armor/orc_boot_r" : "wear right boot",
                ]));
    SetRace("orc");
    SetLevel(5);
    SetClass("fighter");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
    SetWanderSpeed(3);
}

void init(){
    ::init();
}
