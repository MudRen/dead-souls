#include <lib.h>
#include <medium.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(10);
    SetShort("电梯井");
    SetLong("电梯井。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "east" : "/domains/campus/room/science7",
                ]) );
    SetSinkRoom("/domains/campus/room/shaft1");
    SetDoor("east", "/domains/campus/doors/eledoor2");
    SetMedium(MEDIUM_AIR);
}
void init(){
    ::init();
}
