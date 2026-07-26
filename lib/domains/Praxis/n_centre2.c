#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "普拉克西斯北端");
    SetLong(
            "当你接近普拉克西斯最北端时，中心路变成了一条穿过"
            "北方森林的小径。向南，小径通往这座宏伟村庄的中心。"
            "西边有一家小医院。太阳巷向东延伸。");
    SetExits(
            (["north" : "/domains/Praxis/forest1",
             "south" : "/domains/Praxis/n_centre1",
             "east" : "/domains/Praxis/sun1",
             "west"	 : "/domains/Praxis/hospital"]) );
    SetItems(
            (["path" : "中心路向南通往克拉斯纳广场，向北出城。",
             "road" : "博克拉路是主要的东西向道路。",
             "church" : "一座由当地牧师管理的小教堂。",
             "forest" : "北方森林。人迹罕至。",
             "village" : "宏伟的普拉克西斯村庄",
             "hospital" : "一座白色建筑，从景观中突出"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
