#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("壁龛");
    SetLong("一个壁龛。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetInventory(([
                "/domains/campus/weap/board" : 1,
                ]));
    SetExits(([
                "east" : "/domains/campus/room/weaplab",
                ]));
}

void init(){
    ::init();
}
