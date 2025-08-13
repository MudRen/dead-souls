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
    SetShort("村庄道路交叉口");
    SetNightLong("你位于村庄的主要交叉口，被路灯照亮。萨奎弗路向北和向南延伸，被一条东西向的道路横穿，这条路向西通往荒野，向东通往海岸。\n%^GREEN%^这里有一个标牌，你可以使用'read sign'命令阅读。%^RESET%^");
    SetDayLong("你位于村庄的主要交叉口。萨奎弗路向北和向南延伸，被一条东西向的道路横穿，这条路向西通往荒野，向东通往海岸。\n%^GREEN%^这里有一个标牌，你可以使用'read sign'命令阅读。%^RESET%^");
    SetItems( ([
                "sign":"路边的一个大标牌。要阅读它，请使用'read sign'命令。",
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
