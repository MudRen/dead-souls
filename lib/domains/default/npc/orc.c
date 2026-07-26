#include <lib.h>

inherit LIB_NPC;

protected void create() {
    npc::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"dirty"}));
    SetShort("一个肮脏的兽人");
    SetLong("这个兽人是其种族的典型代表：肮脏、野蛮、矮小。它似乎是幼年或青少年，这使得它 somewhat less dangerous but more hostile。");
    SetLevel(1);
    SetRace("orc");
    SetGender("male");
    SetMaxHealthPoints(100);
    SetEncounter(0);
    SetInventory(([
                "/domains/default/weap/axe":"wield axe",
                ]) );

}
void init(){
    ::init();
}
