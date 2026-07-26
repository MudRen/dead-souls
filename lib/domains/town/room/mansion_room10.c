#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("餐厅");
    SetLong("这间大房间呈长方形，显然被用作正式餐厅。美丽的挂毯和画作装饰着墙壁，这里有一种庄严肃穆的氛围。");
    SetItems( ([
                ({"tapestry","tapestries"}) : "这里引人入胜的挂毯似乎记录了诺曼国王征服英格兰的故事。",
                ({"painting","paintings"}) : "这些是文艺复兴时期贵族的非凡油画肖像，画得栩栩如生，令人惊叹。",
                ]) );
    SetInventory( ([ 
                "/domains/town/obj/dining_table" : 1,
                ]) );
    SetExits( ([
                "east" : "/domains/town/room/mansion_dhall2"
                ]) );
}
void init(){
    ::init();
}
