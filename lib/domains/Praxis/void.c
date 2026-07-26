#include <lib.h>

inherit LIB_ROOM;

void create() {
    room::create();
    SetShort("虚空");
    SetLong("虚空。向下走可离开。");
    SetExits(([ "down": "/domains/Praxis/square" ]));
}
void init(){
    ::init();
}
