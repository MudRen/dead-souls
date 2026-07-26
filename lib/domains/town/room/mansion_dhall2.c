#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园楼下走廊");
    SetLong("你在庄园装饰精美的楼下走廊里。东西两侧都有房间，走廊继续向南延伸。北边是入口门厅。");
    SetItems( ([
                "hallway" : "通往房屋其他地方的室内通道。",
                ({"mansion","house"}) : "你身处一座美丽的庄园之中。",
                "foyer" : "庄园的入口区在北边。"
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/mansion_int",
                "south" : "/domains/town/room/mansion_dhall3",
                "west" : "/domains/town/room/mansion_room10",
                "east" : "/domains/town/room/mansion_room7.c",
                ]) );

}
void init(){
    ::init();
}
