#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("村庄小径");
    SetNightLong("虽然仍有灯柱照亮，但村庄道路在这里变得更像一条土路而非道路。从这里几乎可以看到东海的海岸。村学堂在北边，海岸在东边，村庄马厩在南边。");
    SetDayLong("从西向东延伸，村庄道路在这里变得更像一条土路而非道路。从这里几乎可以看到东海的海岸。村学堂在北边，海岸在东边，村庄马厩在南边。");
    SetItems(([
                ({ "building", "schoolhouse", "school", "village school", "village schoolhouse" }) : "一座小巧但维护良好的木制建筑，镇民和他们的孩子来这里获取知识。",
                ({ "building", "buildings" }) : "供人类居住的建筑结构。",
                ({ "shore", "village shore" }) : "东海的海岸在东边。",
                ]));
    SetSkyDomain("town");
    AddTerrainType(T_ROAD);
    SetExits( ([
                "west" : "/domains/town/room/vill_road3",
                "north" : "/domains/town/room/school",
                "east" : "/domains/town/room/shore",
                "south" : "/domains/town/room/stables.c",
                ]) );
    SetEnters( ([ 
                ]) );
    AddItem(new("/domains/town/obj/lamp"));
}
void init(){
    ::init();
}
