#include <lib.h>

inherit "/domains/cave/etc/cave_orc";

int GetEnemyChaser() { return 1; }

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc","soldier"}));
    SetAdjectives(({"orc","armored","professional","soldier"}));
    SetShort("一个兽人士兵");
    SetLong("这是一个高大的兽人士兵。");
    SetInventory(([
                "/domains/cave/weap/longsword" : "wield sword",
                "/domains/cave/armor/chainmail" : "wear chainmail",
                "/domains/cave/armor/orc_boot_l" : "wear left boot",
                "/domains/cave/armor/orc_boot_r" : "wear right boot",
                ]));
    SetRace("orc");
    SetLevel(7);
    SetClass("fighter");
    SetGender("male");
    SetEncounter(  (: CheckOrc :) );
    SetWanderSpeed(5);
}

void init(){
    ::init();
}
