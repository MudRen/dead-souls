#include <terrain_types.h>
#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetShort("要塞之路");
    SetNightLong("你在村庄北端的道路上。南边是镇中心。第一村镇银行就在道路东侧。西边是邮局。");
    SetDayLong("你在一条南北向的道路上。南边是镇中心。北边道路沿着狭窄的山脊延伸，通向看起来像要塞的地方。第一村镇银行就在道路东侧。西边是邮局。");
    SetItems( ([
                ({"rubble","stone","stones","road"}) : "看起来"
                "道路仍在建设中。向北进一步旅行"
                "是不可能的。",
                ({"mountains","beautiful","snow-capped mountains"}) : "美丽的"
                "群山，在遥远的北方天际。"
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
