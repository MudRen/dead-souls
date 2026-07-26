#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("西村路");
    SetDayLong("这是一条繁忙的道路，向东通往城镇，向西远离城镇。城镇教堂在北边。");
    SetSkyDomain("town");
    SetExits( ([
                "north" : "/domains/town/room/church",
                "east" : "/domains/town/room/start",
                "west" : "/domains/town/room/road2",
                ]) );
    SetNightLong("这是一条繁忙的道路，由灯光照亮。向东通往城镇，向西远离城镇。城镇教堂在北边。");
    AddTerrainType(T_ROAD);
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
