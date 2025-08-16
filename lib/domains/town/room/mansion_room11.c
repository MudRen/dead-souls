#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("秘密房间");
    SetLong("你在一个小而狭窄的房间内。");
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
