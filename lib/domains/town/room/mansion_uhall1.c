#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园楼上走廊北端");
    SetLong("你在庄园装饰精美的楼上走廊里。东西两侧都有房间，走廊继续向南延伸。走廊尽头的一扇开着的窗户可以通向楼下。");
    SetItems( ([
                ({"window","open window"}) : "这里一扇开着的窗户通往庄园外部。",
                ({"hall","hallway"}) : "连接庄园各区域的走廊。"
                ]) );
    SetExits( ([
                "down" : "/domains/town/room/mansion_ext",
                "south" : "/domains/town/room/mansion_uhall2",
                "east" : "/domains/town/room/mansion_room1",
                "west" : "/domains/town/room/mansion_room2",
                "window" : "/domains/town/room/mansion_ext"
                ]) );
    SetEnters( ([
                "window" : "/domains/town/room/mansion_ext"
                ]) );

    SetDoor("east", "/domains/town/doors/m1.c");

    SetDoor("west", "/domains/town/doors/m2.c");

}
void init(){
    ::init();
}
