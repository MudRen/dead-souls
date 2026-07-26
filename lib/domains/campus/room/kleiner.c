#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("克莱纳博士的办公室");
    SetLong("克莱纳博士处理行政事务的地方。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "south" : "/domains/campus/room/science7",
                "east" : "/domains/campus/room/klab.c",
                ]) );
}

void init(){
    ::init();
}
