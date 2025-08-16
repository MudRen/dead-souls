#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("餐厅");
这个大房间呈长方形，显然用作正式的餐厅。美丽的挂毯和画作装饰着墙壁，这里有一种庄严的威严感。
    SetItems( ([
                ({"tapestry","tapestries"}) : "这里迷人的挂毯似乎记录了诺曼国王征服安格利亚的历史。"
                ({"painting","paintings"}) : "这些是文艺复兴时期贵族的非凡油画肖像，它们以一种怪异逼真的现实主义手法呈现。"
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
