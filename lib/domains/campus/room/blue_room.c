#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("蓝房间");
    SetLong("这是一个蓝房间。概率实验室一在南边。");
    SetExits( ([
                "south" : "/domains/campus/room/monty"
                ]) );
    SetDoor("south","/domains/campus/doors/blue_door");
}

void init(){
    ::init();
}
