#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆二楼走廊");
    SetLong("你在公馆装饰精美的二楼走廊里。"
            "东边和西边都有房间，走廊"
            "向北和向南延伸。"); 
    SetItems( ([
                ({"hall","hallway"}) : "一条连接公馆各个部分的走廊。"
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
