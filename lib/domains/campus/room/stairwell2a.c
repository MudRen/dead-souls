#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼楼梯间，一楼");
    SetLong("这是大学科学楼一楼的楼梯间。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "north" : "/domains/campus/room/science6",
                "west" : "/domains/campus/room/alcove1",
                "up" : "/domains/campus/room/stairwell2b",
                "down" : "/domains/campus/room/stairwell2c.c",
                ]) );
}

void init(){
    ::init();
}
