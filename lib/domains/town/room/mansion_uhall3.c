#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆二楼走廊南端");
    SetLong("你在公馆装饰精美的二楼走廊里。"
            "东边和西边都有房间，走廊"
            "向北延伸。主卧室在南边。一个大型"
            "圆形大理石楼梯通向一楼。"); 
    SetItems( ([
                ({"hall","hallway"}) : "一条连接公馆各个部分的走廊。"
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
