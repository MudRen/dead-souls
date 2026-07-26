#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetSmell( "default", "淡淡的树叶清香向你飘来。");
    SetShort( "普拉克西斯东端");
    SetLong(
            "土路带你来到普拉克西斯村庄的尽头。博克拉路与一条"
            "更小的土路相交汇，继续向东通往荒野。小径非常狭窄，"
            "看起来不太安全。走了几米后，它突然被大量绿色树叶"
            "和灌木丛吞没。前方，你可以看到东大道更暗的路径，"
            "通往普拉克西斯的墓地。向西可以回到东博克拉路。");
    SetItems(
            (["road" : "通往村庄中心的西边。",
             "village" : "普拉克西斯是噩梦世界的一个小型冒险社区。",
             "wilderness" : "传说荒野中有土匪和恶徒出没。",
             "path" : "小径从这里通往多个方向：普拉克西斯墓地、荒野，"
             "以及回到纪念碑广场。",
             "cemetery": "普拉克西斯墓地位于东大道北边。"]) );
    SetSkyDomain("town");
    SetExits( ([ 
                "west" : "/domains/Praxis/e_boc_la2",
                "north" : "/domains/Praxis/east_road1",
                "east" : "/domains/Praxis/wild1",
                ]) );
}
void init(){
    ::init();
}
