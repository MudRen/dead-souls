#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("堡垒路");
    SetNightLong("你在村庄北缘的一条路上。南边是城镇的中心。村庄第一银行位于路的东侧。西边是邮局。");
    SetDayLong("你在一条南北向的路上。南边是城镇的中心。北边，道路沿着一条狭窄的山脊延伸，通往看起来像堡垒的地方。村庄第一银行位于路的东侧。西边是邮局。");
    SetItems( ([
                ({"rubble","stone","stones","road"}) : "看起来这条路还在修建中。无法继续向北前进。",
                ({"mountains","beautiful","snow-capped mountains"}) : "美丽的山脉，远在北方的地平线上。"
                ]) );
    SetSkyDomain("town");
    SetExits( ([
                "south" : "/domains/town/room/road",
                "east" : "/domains/town/room/bank",
                "west" : "/domains/town/room/postoffice.c",
                ]) );
    if(!strsrch(mud_name(), "Dead Souls")){
        if(directory_exists("/domains/fort")){
            AddExit("north", "/domains/fort/room/f_road4");
        }
    }
    AddTerrainType(T_ROAD);
    AddItem(new("/domains/town/obj/lamp"));
    if(file_exists("/domains/fort/room/f_road4.c")){
    }
}
void init(){
    ::init();
}
