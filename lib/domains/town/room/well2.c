#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("水道隧道");
    SetLong("这条黑暗的隧道看起来是在基岩中粗糙地开凿出来的，向西倾斜而下。这似乎是地下泉水供给镇水井的通道。隧道东西两端各有一扇门。");
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
