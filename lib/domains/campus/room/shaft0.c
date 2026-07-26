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
                "east" : "/domains/campus/room/basement3.c",
                ]) );
    SetDoor("east","/domains/campus/doors/steel_door3");
    SetFlyRoom("/domains/campus/room/shaft1");
    SetSinkRoom("/domains/campus/room/shaftb");
    SetMedium(MEDIUM_AIR);
}

void init(){
    ::init();
}
