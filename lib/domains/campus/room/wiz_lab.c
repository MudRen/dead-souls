#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("实验室翼");
    SetLong("这是一个明亮、闪亮的实验室综合体，连接着进行概率实验的实验室。概率实验目前在南边和西南边的实验室运行。东边的实验室可供一般使用。科学楼主走廊在北边。");
    SetItems( ([
                ({"lab","laboratory","wing","complex"}) : "你在实验室综合体。可以从这里进入各个实验室。",
                ({"stairs","downstairs"}) : "下楼回到创建者大厅。"
                ]) );
    SetExits( ([
                "south" : "/domains/campus/room/monty",
                "north" : "/domains/campus/room/science1",
                "east" : "/domains/campus/room/plab",
                "southwest" : "/domains/campus/room/plab2.c",
                ]) );

    SetDoor("north", "/domains/campus/doors/prob_door.c");

}
void init(){
    ::init();
}
