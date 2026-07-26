#include <lib.h>

inherit LIB_ROOM;

protected void create() {
    object ob;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("测试实验室走廊西侧");
    SetLong("这是测试实验室主走廊的西端。北边是疾病实验室。创造者大厅在西边，走廊向东延伸。");
    SetExits( ([ 
                "north" : "/domains/default/room/quarantine1",
                "east" : "/domains/default/room/wiz_corr_east",
                "west" : "/domains/default/room/wiz_hall",
                ]) );

    SetInventory(([
                ]));

    SetProperty("no attack", 1);

}
int CanReceive(object ob) {
    return room::CanReceive();
}

void init(){
    ::init();
}
