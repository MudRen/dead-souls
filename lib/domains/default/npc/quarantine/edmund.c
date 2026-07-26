#include <lib.h>

inherit LIB_NPC;


protected void create() {
    npc::create();
    SetKeyName("Edmund");
    SetId(({"edmund"}));
    SetShort("埃德蒙");
    SetLong("埃德蒙是一名来自英国的交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
