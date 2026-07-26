#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

int readSign() {
    this_player()->more("/domains/town/txt/hints_sign.txt");
    return 1;
}

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("村庄路口");
    SetNightLong("你在村庄的主要路口，由城镇灯柱照亮。萨奎沃路南北延伸，与一条东西向的道路交汇，西边通往荒野，东边通往海岸。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetDayLong("你在村庄的主要路口。萨奎沃路南北延伸，与一条东西向的道路交汇，西边通往荒野，东边通往海岸。\n%^GREEN%^这里有一块你可以阅读的告示牌。%^RESET%^");
    SetItems( ([
                "sign":"路上的一块大告示牌。输入 'read sign' 来阅读。",
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "south" : "/domains/town/room/south_road1",
                "east" : "/domains/town/room/vill_road2",
                "west" : "/domains/town/room/road1",
                "north" : "/domains/town/room/road0.c",
                ]) );
    AddTerrainType(T_ROAD);
    SetNoModify(0);
    SetInventory(([
                "/domains/town/obj/clocktower" : 1,
                ]));
    SetEnters( ([
                ]) );
    SetRead("sign", (: readSign :) );
    AddItem(new("/domains/town/obj/lamp"));
}

void init(){
    ::init();
}
