#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆二楼走廊北端");
    SetLong("你在公馆装饰精美的二楼走廊里。"
            "东边和西边都有房间，走廊"
            "向南延伸。走廊尽头有一扇开着的窗户"
            "通向下。");
    SetItems( ([
                ({"window","open window"}) : "这里有一扇开着的窗户"+
                "通向公馆外部。",
                ({"hall","hallway"}) : "一条连接公馆各个部分的走廊。"
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
