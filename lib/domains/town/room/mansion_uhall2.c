#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园楼上走廊");
    SetLong("你在庄园装饰精美的楼上走廊里。东西两侧都有房间，走廊继续向南北延伸。");
    SetItems( ([
                ({"hall","hallway"}) : "连接庄园各区域的走廊。"
                ]) );
    SetExits( ([
                "south" : "/domains/town/room/mansion_uhall3",
                "north" : "/domains/town/room/mansion_uhall1",
                "east" : "/domains/town/room/mansion_room3",
                "west" : "/domains/town/room/mansion_room4"
                ]) );

    SetDoor("west", "/domains/town/doors/m4.c");

    SetDoor("east", "/domains/town/doors/m3.c");

}
void init(){
    ::init();
}
