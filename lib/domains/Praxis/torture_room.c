#include <lib.h>

inherit LIB_ROOM;

void create() {
    ::create();
    SetProperties( ([ "indoors" : 1, "light" : 1, "no killing" : 1, 
                "no stealing" : 1, "no magic" : 1, "no teleport" : 1 ]) );
    SetShort("拷问室");
    SetLong("你在臭名昭著的拷问大厅里，一个普拉克西斯守卫"
            "只对最恶劣的罪犯使用的小房间。"
            "从房间中央桌子上的有利位置，你无法收集到"
            "太多关于周围环境的信息。然而，你可以"
            "看到散落在房间各处的各种器具，覆盖着灰尘和蜘蛛网。");
    SetItems( ([ "devices" : "用于执行残忍和不寻常惩罚的各种机械器具。",
                "table" : "一张不舒服的水泥桌。"]) );
    SetSmell("default", "空气中弥漫着腐烂尸体的刺鼻气味。");
}

void init() {
    ::init();
    if(this_player()->query_ghost()) 
        this_player()->move("/domains/Mountains/cave/cave3");
}
