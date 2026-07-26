#include <lib.h>

inherit "/domains/cave/etc/cave_orc";

int GetEnemyChaser() { return 0; }

protected void create() {
    ::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"armored","professional"}));
    SetShort("一个武装兽人");
    SetLong("这是一个高大的成年兽人，举止专业，目标明确。");
    SetInventory(([
                "/domains/cave/weap/axe" : "wield axe",
                "/domains/cave/armor/leather_armor" : "wear leather armor",
                "/domains/cave/armor/orc_boot_l" : "wear left boot",
                "/domains/cave/armor/orc_boot_r" : "wear right boot",
                ]));
    SetRace("orc");
    SetLevel(3);
    SetClass("fighter");
    SetGender("male");
    this_object()->SetGuard("northeast","The orc bars your way!");
}

void init(){
    ::init();
}
