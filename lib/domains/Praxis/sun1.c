#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 4);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "中心路附近的太阳巷");
    SetLong(
            "太阳巷是一条明亮的小路，因阳光似乎总是照耀着它而得名。"
            "小路相当安静，只有偶尔出来散步或办事的村民。"
            "小巷位于村庄北边，与西边的中心路相交。"
            "南边你可以看到一间棕色的茅草屋。");
    SetItems(
            (["alley" : "明亮而欢快，不像南边那条小巷。",
             "path" : "普拉克西斯的主要南北向道路。",
             "intersection" : "太阳巷在那里与中心路交汇。",
             "house" : "一间小小的茅草屋，没什么特别的。"]) );
    SetSkyDomain("town");
    SetExits( 
            (["east" : "/domains/Praxis/sun2",
             "west" : "/domains/Praxis/n_centre2",
             "south"	 : "/domains/Praxis/house"]) );
}
void init(){
    ::init();
}
