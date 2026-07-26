#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学教室");
    SetLong("这个小房间为该设施研究的高级课题提供教学空间。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits(([
                "south" : "/domains/campus/room/science5",
                ]));
}

void init(){
    ::init();
}
