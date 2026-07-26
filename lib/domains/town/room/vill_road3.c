#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("东村路");
    SetNightLong("一条灯光照亮的长路穿过村庄。市政厅在北边。城镇的主要部分在西边。");
    SetDayLong("一条长路穿过村庄。市政厅在北边。城镇的主要部分在西边。");
    SetItems(([
                ({ "office", "post office" }) : "可以在邮局收发邮件。",
                ({ "building", "buildings" }) : "供人类居住的建筑结构。",
                ({ "hall", "town hall" }) : "这是一座朴素的建筑，镇上公务在此办理。",
                ]));
    SetSkyDomain("town");
    SetExits( ([ 
                "north" : "/domains/town/room/thall",
                "east" : "/domains/town/room/vill_road4",
                "west" : "/domains/town/room/vill_road2",
                ]) );
    AddTerrainType(T_ROAD);
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
