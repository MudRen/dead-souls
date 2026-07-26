#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("no castle", 1);
    SetShort( "一条土路公路");
    SetLong(
            "你发现自己在一条宽阔的土路上，向西通往普拉克西斯以外的地方。"
            "远处，达洛克山脉雄伟地耸立在平坦的平原之上。"
            "这片区域相当稀疏，只有零星几棵树。"
            "很久以前这里曾经有草地，但被众多穿越此地的冒险者破坏了。"
            "向东通往西博克拉路，向西通往公路。");
    SetItems(
            (["highway" : "连接普拉克西斯与噩梦世界西部土地的公路。",
             ({ "trees", "tree" }) : "树木非常矮小。这里不太适合它们生长。",
             "village" : "一个小小的冒险村庄。那里有很多服务设施。",
             "mountains" : "达洛克山脉远在西边。"
             ]) );
    SetSkyDomain("town");
    SetExits( 
            (["west" : "/domains/Praxis/highway2",
             "east" : "/domains/Praxis/w_boc_la3"]) );
}
void init(){
    ::init();
}
