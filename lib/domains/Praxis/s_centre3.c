#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("普拉克西斯南部");
    SetDayLong( "普拉克西斯南部是这个小型冒险社区的商业区。"
            "中心路从中穿过，将人们从镇中心带到这里，"
            "向西南方向，马匹和行人的交通开始繁忙起来。");
    SetNightLong( "普拉克西斯的商业区几乎陷入沉睡，"
            "只有少数夜间活动的冒险者。中心路从北方蜿蜒而下，"
            "向西南通往普拉克西斯港口。一条无名路向东延伸。");
    SetExits(
            (["north" : "/domains/Praxis/s_centre2",
             "southwest" : "/domains/Praxis/s_centre4",
             "east" : "/domains/Praxis/unnamed1"]) );
    SetItems(
            ([({"path", "centre path"}) : "贯穿普拉克西斯南北的主要道路。",
             ({"port", "port of praxis"}) : "从这里看不到。",
             ({"road", "unnamed road"}) : "通往城外。"]) );
    SetSkyDomain("town");
    SetListen("road", "那个方向弥漫着一种诡异的寂静。");
}
void init(){
    ::init();
}
