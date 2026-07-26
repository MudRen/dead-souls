#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("测试实验室走廊东侧");
    SetLong("这是测试实验室的主走廊。走廊向东和向西延伸。南边是星门实验室。");
    SetExits( ([
                "east" : "/domains/default/room/wiz_corr_east3",
                "west" : "/domains/default/room/wiz_corr_east",
                "south" : "/domains/default/room/stargate_lab.c",
                ]) );
    SetProperty("no attack", 1);
}

int CanReceive(object ob) {
    return room::CanReceive();
}

void init(){
    ::init();
}
