#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("绿房间");
    SetLong("这是一个绿房间。概率实验室三在西边。");
    SetExits( ([
                "west" : "/domains/campus/room/plab"
                ]) );
    SetDoor("west","/domains/campus/doors/green_door3");
}
void init(){
    ::init();
}
