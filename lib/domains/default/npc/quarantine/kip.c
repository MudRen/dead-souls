#include <lib.h>

inherit LIB_NPC;

protected void create() {
    npc::create();
    SetKeyName("Kip");
    SetId(({"kip"}));
    SetShort("基普");
    SetLong("基普是一名来自荷兰的交换生。");
    SetMelee(1);
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
