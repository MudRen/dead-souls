#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperty("light", 2);
    SetProperty("night light", 1);
    SetProperty("no castle", 1);
    SetShort( "兽人堡垒中的开阔庭院");
    SetLong(
            "你周围的庭院被古老的石墙环绕，"
            "赋予这座堡垒坚不可摧的气息。南面一座壮观的"
            "拱门通向兽人谷。东西方向各有一条通道。");
    SetItems(
            (["courtyard" : "一个四面被石墙围住的开阔院子。",
             "yard" : "这里没有屋顶，但墙壁太高了，你只能看到天空。",
             "stone" : "一块来源不明的灰色石头，上面刻有文字。",
             "walls" : "你无法以超自然的方式越过它们。",
             "fortress" : "它看起来极其古老。",
             "arch" : "堡垒巨大而守卫森严的入口。",
             "archway" : "它构成了堡垒巨大而守卫森严的入口。",
             "valley" : "从庭院内部你看不到它的任何部分。",
             "passages" : "它们通向堡垒的内部。",
             "passage" : "你完全不知道它会通向哪里。"]) );
    SetExits( 
            (["east" : "/domains/Praxis/orc_valley/passage1",
             "west" : "/domains/Praxis/orc_valley/passage2",
             "north" : "/domains/Praxis/orc_valley/shaman",
             "south" : "/domains/Praxis/orc_valley/guard"]) );
    SetSearch( 0, "搜索什么？");
    SetSearch( "walls", "你注意到北墙上有一条秘密通道。");
    SetSearch("wall", "哪面墙？");
    SetSearch("north wall", "你注意到一条秘密通道。");
}

void init(){
    ::init();
}
