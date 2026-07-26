#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("西村路");
    SetNightLong("这是一条繁忙的道路，由灯光照亮。向东通往城镇，向西通往一座古老的拱桥。南边是一座宏伟的庄园。");
    SetDayLong("这是一条繁忙的道路，向东通往城镇，向西远离城镇。西边有一座古老的拱桥。南边是一座宏伟的庄园。");
    SetItems(([
                ({ "fort", "fortress", "fortress in the distance" }) : "从这里看不清楚，但北方远处似乎是一座建在高原上的大型堡垒。",
                ({ "road", "roads" }) : "这是一条简单的东西向道路，向东通往城镇，向西远离城镇。另一条鹅卵石路在这里与北方交汇，通往远处高原上的堡垒。",
                "cobblestone road" : "一条鹅卵石路从这里开始，沿着陡峭的斜坡向上延伸，通往北方的高原。",
                ]));
    SetSkyDomain("town");
    SetExits( ([
                "east" : "/domains/town/room/road1",
                "west" : "/domains/town/room/bridge",
                "south" : "/domains/town/room/gate.c",
                ]) );
    AddTerrainType(T_ROAD);
    AddItem(new("/domains/town/obj/lamp"));
}

void init(){
    ::init();
    if(mud_name() == "Dead Souls Omega" && !GetExit("north")){
    }
}
