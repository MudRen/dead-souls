#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("庄园门厅");
    SetLong("这是一座宏伟庄严庄园的门厅。奇怪的是，到处都是灰尘，但这里看起来依然美丽。一条走廊从这里向南延伸。");
    SetItems( ([
                "foyer" : "这是庄园的室内入口区域，前门就在这里。",
                ({"hall","hallway"}) : "一条通往庄园其他区域的宽阔走廊。",
                "dust" : "散布在可见表面上的微小颗粒物质。"
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
