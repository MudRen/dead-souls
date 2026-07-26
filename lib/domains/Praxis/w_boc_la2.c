#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort("西博克拉路");
    SetDayLong( "普拉克西斯西区是一个更加乡村化的区域。"
            "南边是开阔的农田，北边排列着小屋和房屋。道路继续"
            "沿东西方向延伸。");
    SetNightLong("路灯照亮了西普拉克西斯乡村街道，北边的小屋"
            "和房屋以及南边的农田都被灯光映照。道路向东西"
            "两个方向继续延伸。");

    SetSmell("default", "一缕缕带有魔法气息的烟雾从西博克拉路"
            "北边的一所房屋升起。");
    SetSmell("smoke", "闻起来不像你曾经遇到过的任何物质。");
    SetSmell("house", "闻起来像是从里面飘出的魔法烟雾。");
    SetExits(
            (["east" : "/domains/Praxis/w_boc_la1",
             "west" : "/domains/Praxis/w_boc_la3",
             "south" : "/domains/Praxis/farm",
             "north" : "/domains/Praxis/sage_room"]) );
    SetItems(
            (["road" : "博克拉路贯穿普拉克西斯东西方向。",
             "roads" : "西大道和博克拉路。",
             "highway" : "通往噩梦世界西部土地的繁忙公路。当心达洛克山脉。",
             "mountains" : "达洛克山脉。据传有邪恶生物栖息其中。",
             "house" : "这所小房子的门窗冒出缕缕白烟。",
             "smoke" : "缕缕白烟从北边的房子里飘出来。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
