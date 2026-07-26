#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼，二楼");
    SetLong("这是LPC大学科学楼的二楼。西边是一扇电梯门。");
    SetClimate("indoors");
    SetExits( ([
                "north" : "/domains/campus/room/kleiner",
                "south" : "/domains/campus/room/stairwell2b",
                "west" : "/domains/campus/room/shaft2.c",
                ]) );
    SetDoor("west", "/domains/campus/doors/eledoor2");
}

void init(){
    ::init();
}
