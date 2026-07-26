#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("书房");
    SetLong("你在主人的书房里。这个房间一片狼藉！看起来被人匆忙地洗劫过。如果这里曾经有什么值钱的东西，恐怕早就不见了。");
    SetExits( ([
                "west" : "/domains/town/room/mansion_uhall3"
                ]) );

    SetDoor("west", "/domains/town/doors/m5.c");

}
void init(){
    ::init();
}
