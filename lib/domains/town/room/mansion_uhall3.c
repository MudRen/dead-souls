#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园楼上走廊南端");
    SetLong("你在庄园装饰精美的楼上走廊里。东西两侧都有房间，走廊继续向北延伸。主卧室在南边。一座大型圆形大理石楼梯通往一楼。");
    SetItems( ([
                ({"hall","hallway"}) : "连接庄园各区域的走廊。"
                ]) );

    SetExits( ([
                "south" : "/domains/town/room/mansion_mbdroom",
                "north" : "/domains/town/room/mansion_uhall2",
                "down" : "/domains/town/room/mansion_dhall3",
                "east" : "/domains/town/room/mansion_room5",
                "west" : "/domains/town/room/mansion_room6"
                ]) );

    SetDoor("east", "/domains/town/doors/m5.c");

    SetDoor("west", "/domains/town/doors/m6.c");

    SetDoor("south", "/domains/town/doors/m7.c");

}
void init(){
    ::init();
}
