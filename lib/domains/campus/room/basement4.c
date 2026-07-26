#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("秘密实验室");
    SetLong("这个房间似乎被用于秘密实验。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits(([
                "west" : "/domains/campus/room/basement3",
                ]));
}

void init(){
    ::init();
}
