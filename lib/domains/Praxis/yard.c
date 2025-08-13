#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 2);
    SetProperty("no castle", 1);
    SetShort("一个小庭院");
    SetDayLong( "白天让这条小巷尽头美丽的小庭院充满宁静祥和。古朴的房屋环绕着庭院 "
            "四周，只有西侧小巷与中心大道相交的地方除外。在小巷与庭院 "
            "交界处有一个检修孔。");
    SetNightLong( "在漆黑的夜晚，这条小巷尽头很少有动静。一些光线从 "
            "环绕小巷尽头庭院的房屋前方路灯照亮了这片区域。");

    SetDoor("/domains/Praxis/sewer_ent","down");
    "/domains/Praxis/sewer_ent"->SetOpen("manhole", 0);
    SetExits( 
            (["west" : "/domains/Praxis/s_centre2",
             "north" : "/domains/Praxis/sheriff",
             "down" : "/domains/Praxis/sewer_ent"]) );
    SetItems(
            (["alley" : "这里看起来很美丽。",
             ({ "lamp", "lamps" }) : "昏暗的灯光。",
             "manhole" : (: this_object(), "look_at_manhole" :) ]) );
    SetSkyDomain("town");
    SetInventory(([
                "/domains/Praxis/obj/mon/beggar" : 1,
                ]));
}

void reset() {
    ::reset();
    if(!find_living("beggar") || !environment(find_living("beggar")))
        new("/domains/Praxis/obj/mon/beggar")->move(this_object());
    if(query_reset_number() != 1) {
        "/domains/Praxis/sewer_ent"->SetOpen("manhole", 0);
    }
}
void init(){
    ::init();
}
