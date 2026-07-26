#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("秘密实验室");
    SetLong("这个位于校园各层之间的整洁工作空间似乎是某种秘密实验室。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetInventory(([
                "/domains/campus/weap/zpem" : 1,
                ]));
    SetExits( ([
                "west" : "/domains/campus/room/shaft0",
                "east" : "/domains/campus/room/basement4.c",
                ]) );
    SetDoor("west","/domains/campus/doors/steel_door3");
}

void init(){
    ::init();
}
