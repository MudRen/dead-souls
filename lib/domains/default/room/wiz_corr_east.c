#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("测试实验室走廊");
    SetLong("这是测试实验室的主走廊。北边是竞技场。南边是动物园。走廊向东和向西延伸。");
    SetExits( ([
                "south" : "/domains/default/room/wiz_corr_south",
                "west" : "/domains/default/room/wiz_corr1",
                "north" : "/domains/default/room/arena",
                "east" : "/domains/default/room/wiz_corr_east2.c",
                ]) );
    SetInventory(([
                ]));


    SetDoor("north", "/domains/default/doors/steel_door2.c");

}
int CanReceive(object ob) {
    return room::CanReceive();
}

void init(){
    ::init();
}
