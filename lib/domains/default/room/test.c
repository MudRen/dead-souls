#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("起始房间");
    SetLong("默认起始房间。向下走可以进入一组示例房间。");
    SetExits( ([ 
                "down" : "/domains/town/room/road",
                ]) );
}
void init(){
    ::init();
}
