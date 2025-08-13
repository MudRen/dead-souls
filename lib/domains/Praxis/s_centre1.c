#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetListen("default", "喧闹的噪音从西侧酒馆里传出。");
    SetShort( "拉尔斯酒馆外的中心大道");
    SetLong(
            "中心大道穿过普瑞克斯商业区的心脏地带，一路向下通往著名的普瑞克斯港口。"
            "可以看到粗鲁的顾客们正朝着西侧的拉尔斯酒馆走去。"
            "这座建筑非常古老破旧。许多醉酒冒险者的虐待已开始对这座建筑造成损害。"
           );
    SetExits( 
            (["north" : "/domains/Praxis/square",
             "south" : "/domains/Praxis/s_centre2",
             "west" : "/domains/Praxis/pub"]) );
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetItems(
            (["path" : "中心大道向南通往纪念碑广场，向北通往城外。",
             "road" : "博克拉路是主要的东-西向道路。",
             "pub" : "拉尔斯酒馆，现在大多过时了，但它是原始的。",
             "square" : "普瑞克斯的中心广场。"]) );
    SetSkyDomain("town");
    SetProperty("no castle", 1);
}

void init(){
    ::init();
}
