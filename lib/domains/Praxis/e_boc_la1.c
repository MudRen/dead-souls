#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("修道院南边的东博克拉路");
    SetLong(
            "普拉克西斯东侧的博克拉路是一条通往镇中心纪念碑广场的大土路。"
            "许多脚印把路面踩得平坦，便于行走。"
            "生锈的旧路灯柱矗立在道路两侧，在夜间照亮普拉克西斯。"
            "北边的一条小路通往村庄修道院。东博克拉路从这里继续向东延伸，"
            "市政厅在南边。");
    SetExits(
            (["north" : "/domains/Praxis/monastery",
             "east" : "/domains/Praxis/e_boc_la2",
             "south" : "/domains/Praxis/town_hall.c",
             "west" : "/domains/Praxis/square"]) );
    SetItems(
            (["road" : "博克拉路是贯穿普拉克西斯东西方向的大路。",
             "monastery" : "噩梦世界的僧侣在那里学习和祈祷。",
             "square" : "纪念碑广场是普拉克西斯的中心。"
             "许多冒险者喜欢在那里闲逛，和市民们聊关于普拉克西斯的生活。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
