#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("走廊拐角");
    SetLong("这是走廊的拐角处。科学楼主走廊在北边。一条较小的走廊从这里向西延伸。");
    SetClimate("indoors");
    SetExits( ([
                "west" : "/domains/campus/room/science5",
                "north" : "/domains/campus/room/science3.c",
                ]) );
}

void init(){
    ::init();
}
