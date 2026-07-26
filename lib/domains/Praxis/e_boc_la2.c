#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 3);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetListen( "default", "城镇的喧嚣包围着你。");
    SetShort( "东博克拉路");
    SetLong(
            "向东望去，你可以看到博克拉路与东大道的交叉口。"
            "从这里可以看到两座建筑，北边是霍勒斯杂货店，"
            "南边是冒险者大厅所在的大楼。人们忙碌地来来往往，"
            "各忙各的。");
    SetExits(
            (["north" : "/domains/Praxis/supply",
             "south" : "/domains/Praxis/adv_main",
             "east" : "/domains/Praxis/e_boc_la3",
             "west" : "/domains/Praxis/e_boc_la1"]) );
    SetItems(
            (["shop" : "一个可以买卖物品的小地方。",
             "road" : "一条贯穿普拉克西斯东西方向的土路。",
             "area" : "冒险者们在那里组队和讨论冒险经历。",
             "square" : "从这里看不太清楚。",
             "people" : "人们匆匆走过，几乎不会看你一眼。",
             "hall" : "大厅是普拉克西斯所有冒险者聚集聊天的地方。"]) );
    SetSkyDomain("town");
}
void init(){
    ::init();
}
