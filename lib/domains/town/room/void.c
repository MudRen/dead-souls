#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("虚空");
    SetLong("虚空。向下走即可离开。");
    SetExits( ([ "down" : ROOM_START ]) );
    SetNoModify(1);
}
void init(){
    ::init();
}
