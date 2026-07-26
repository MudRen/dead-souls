#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetShort( "普拉克西斯下水道");
    SetLong(
            "你在普拉克西斯镇地下的小型下水道系统里。"
            "头顶上方有一个通往地面的检修孔。");
    SetSmell("default", "下水道散发着人类排泄物的臭味。");
    SetDoor("/domains/Praxis/yard","up");
    SetProperty("light", 0);
    SetProperty("indoors", 1);
    SetItems(
            ([ "manhole" : "一个通往地面的洞。"]) );
    SetExits( ([ 
                "up" : "/domains/Praxis/yard",
                "east" : "/domains/Praxis/sewer",
                ]) );
}

void reset() {
    ::reset();
    if(!present("sword")) 
        new("/domains/Praxis/obj/weapon/sword")->move(this_object());
}
void init(){
    ::init();
}
