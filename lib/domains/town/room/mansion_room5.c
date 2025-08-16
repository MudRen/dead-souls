#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("书房");
    SetLong("你在房子主人的书房里。"+
            "这个房间一团糟！看起来"+
            "曾被匆忙地洗劫过。如果这里"+
            "曾经有什么值钱的东西，"+
            "现在可能早已不见了。");
    SetExits( ([
                "west" : "/domains/town/room/mansion_uhall3"
                ]) );

    SetDoor("west", "/domains/town/doors/m5.c");

}
void init(){
    ::init();
}
