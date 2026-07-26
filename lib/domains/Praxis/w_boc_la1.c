#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "普拉克西斯西博克拉路");
    SetDayLong("正午时分，广场西南角的当地酒吧生意清淡。"
            "然而，当黄昏降临，你会发现越来越多的人涌入酒吧，"
            "为一天的冒险画上句号。你所在的西博克拉路通往"
            "普拉克西斯的西区，向东通往镇中心。");
    SetNightLong("路灯为你提供勉强够用的光线，但你刚好能看到"
            "东边的克拉斯纳广场和南边的拉斯酒馆。你还能辨认出"
            "北边的一座小教堂，但看不到入口。");

    SetListen("default", "当地冒险者的欢呼声从酒吧里传出来。");
    SetExits(
            (["east" : "/domains/Praxis/square",
             "west" : "/domains/Praxis/w_boc_la2",
             "south" : "/domains/Praxis/pub"]) );
    SetItems(
            (["church" : "看起来入口可能在从纪念碑广场向北的路上。",
             ({"lamps", "lamp", "street lamp"}) : "沿路的所有路灯"
             "在夜间提供微弱的光线。",
             ({"pub", "lars pub", "lars' pub"}) : "当地冒险者"
             "在拉斯酒馆里放松一天的疲劳。",
             ({"road", "west boc la", "boc la"}) : "通往普拉克西斯"
             "西区以外的山区。",
             "square" : "位于普拉克西斯中心，是博克拉路和中心路的交汇处。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
