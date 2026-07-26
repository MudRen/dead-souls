#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("indoors", 1);
    SetProperty("no castle", 1);
    SetSmell("default", "你闻到了香薰的芳香。");
    SetShort( "莫拉的小屋");
    SetLong(
            "一股神秘的气息笼罩着这间原本朴素的小屋，"
            "装饰着来自遥远世界的奇怪物品。"
            "这一定是著名的灵媒莫拉的小屋。");
    SetExits(
            (["west" : "/domains/Praxis/west_road2"]) );
    SetItems(
            (["artifacts" : "你不知道它们是什么或意味着什么。",
             "hut" : "非常奇怪。"]) );
}

void reset() {
    ::reset();
    if(present("mora")) return;
    new("/domains/Praxis/obj/mon/mora")->move(this_object());
}
void init(){
    ::init();
}
