#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼楼梯间，二楼");
    SetLong("这是大学科学楼二楼的楼梯间。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "down" : "/domains/campus/room/stairwell2a",
                "north" : "/domains/campus/room/science7.c",
                ]) );
}

void init(){
    ::init();
}
