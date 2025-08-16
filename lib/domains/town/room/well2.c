#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("水隧道");
    SetLong("这条黑暗隧道似乎是粗略地凿进基岩中的，向西向下倾斜。看起来这是地下泉水供给镇水井的通道。隧道两端都有门。");
    SetItems(([
                ({ "rock", "bedrock" }) : "这是地下深处致密坚硬的岩石。",
                ]));
    SetExits( ([
                "east" : "/domains/town/room/well1",
                "west" : "/domains/town/room/well3.c",
                ]) );
    SetDoor("east", "/domains/town/doors/welldoor1.c");
    SetDoor("west", "/domains/town/doors/welldoor2.c");
    SetFlowLimit(2);
}

void init(){
    ::init();
}
