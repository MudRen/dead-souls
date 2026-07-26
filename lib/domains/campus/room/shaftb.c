#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(10);
    SetShort("电梯井");
    SetLong("电梯井，地下室");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "east" : "/domains/campus/room/sub_basement2.c",
                ]) );
    SetFlyRoom("/domains/campus/room/shaft0");
}
void init(){
    ::init();
}
