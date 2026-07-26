#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetListen("default", "喧闹的噪音从西边的酒馆里传出来。");
    SetShort( "拉斯酒馆外的中心路");
    SetLong(
            "中心路穿过普拉克西斯商业区的核心地带，通往著名的"
            "普拉克西斯港口。可以看到喧闹的顾客们向西前往拉斯酒馆。"
            "这座建筑非常古老且饱经风霜。许多醉酒冒险者的"
            "折腾已经开始让这家店付出代价。"
           );
    SetExits(
            (["north" : "/domains/Praxis/square",
             "south" : "/domains/Praxis/s_centre2",
             "west" : "/domains/Praxis/pub"]) );
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetItems(
            (["path" : "中心路向南通往纪念碑广场，向北出城。",
             "road" : "博克拉路是主要的东西向道路。",
             "pub" : "拉斯酒馆，现在大多已废弃，但它是最早的酒馆。",
             "square" : "普拉克西斯的中央广场。"]) );
    SetSkyDomain("town");
    SetProperty("no castle", 1);
}

void init(){
    ::init();
}
