#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("普瑞克斯的博克拉路西段");
    SetDayLong("广场西南角当地的酒馆在白天高峰期生意寥寥。当黄昏降临，然而，你会注意到更多人走向酒馆，为一天的冒险画上句号。你所处的这条路，博克拉路西段，通往普瑞克斯的西部区域，向东则通往市中心。");
    SetNightLong("街灯为你提供勉强足够的光线，但你可以看到东侧的克拉斯纳广场和南侧的Lars酒馆。你也可以辨认出北侧有一座小教堂，但看不到入口。");

    SetListen("default", "当地冒险者的欢呼声从酒馆里传出。");
    SetExits( 
            (["east" : "/domains/Praxis/square",
             "west" : "/domains/Praxis/w_boc_la2",
             "south" : "/domains/Praxis/pub"]) );
    SetItems( 
            (["church" : "看起来入口可能在从纪念碑广场向北的道路上。",
             ({"lamps", "lamp", "street lamp"}) : "道路沿线的所有街灯"
             "在夜晚提供微弱的光线。",
             ({"pub", "lars pub", "lars' pub"}) : "当地冒险者"
             "在拉尔斯酒馆结束他们的一天。",
             ({"road", "west boc la", "boc la"}) : "它穿过"
             "普瑞克斯的西部区域，一直延伸到山脉。",
             "square" : "在普瑞克斯的中心，是 "
             "博克拉路与中心大道交汇的地方。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
