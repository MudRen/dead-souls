#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼楼梯间");
    SetLong("这是大学科学楼的楼梯间。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "up" : "/domains/campus/room/stairwell2a",
                "down" : "/domains/campus/room/stairwell2d.c",
                ]) );
}

void init(){
    ::init();
}
