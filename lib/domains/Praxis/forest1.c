#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("no castle", 1);
    SetShort( "北方森林");
    SetLong(
            "你正身处普拉克西斯村庄北边的一片巨大森林中。"
            "森林向四面八方延伸，一条小径向北通往森林深处，"
            "向南通往村庄的一条主路。");
    SetExits(
            (["north" : "/domains/Praxis/forest2",
             "south"	 : "/domains/Praxis/n_centre2"]) );
    SetItems(
            (["path" : "穿过巨大北方森林的小径。",
             "forest" : "北方森林。人迹罕至。",
             "village" : "宏伟的普拉克西斯村庄"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
