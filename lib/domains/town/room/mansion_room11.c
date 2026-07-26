#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("密室");
    SetLong("你在一间狭小拥挤的房间里。");
    SetExits( ([
                "out" : "/domains/town/room/mansion_mbdroom",
                "north" : "/domains/town/room/mansion_mbdroom"
                ]) );
    SetInventory( ([
                "/domains/town/obj/safe" : 1,
                ]) );
}
void init(){
    ::init();
}
