#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("公馆门厅");
    SetLong("这是一座宏伟壮观公馆的门厅。奇怪的是，到处都是灰尘，但这个地方看起来仍然很美丽。一条走廊从这里向南延伸。");
    SetItems( ([
                "foyer" : "这是公馆的内部入口区域，前门就在这里。",
                ({"hall","hallway"}) : "一条宽阔的走廊，向南通往公馆的其他部分。",
                "dust" : "分散在可见表面上的微小颗粒物质。"
                ]) );
    SetExits( ([
                "north" : "/domains/town/room/mansion_ext",
                "south" : "/domains/town/room/mansion_dhall2",
                "east" : "/domains/town/room/mansion_room9.c",
                ]) );
    SetDoor("north","/domains/town/doors/mansion");
}
void init(){
    ::init();
}
