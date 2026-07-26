#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 2);
    SetProperty("no castle", 1);
    SetShort( "克拉斯纳广场南侧的中心路");
    SetLong(
            "一条小巷在克拉斯纳广场南侧横穿中心路。"
            "中心路蜿蜒向南，穿过南普拉克西斯的商业中心，"
            "直达普拉克西斯港口。");
    SetExits(
            (["north" : "/domains/Praxis/s_centre1",
             "south" : "/domains/Praxis/s_centre3",
             "east" : "/domains/Praxis/yard",
             "west" : "/domains/Praxis/alley1"]) );
    SetItems(
            ([({ "path", "road", "centre path" }) : "中心路向北通往纪念碑广场，向南通往港口。",
             "alley" : "向东通往一片住宅庭院，向西是邮局和银行。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
