#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("红房间");
    SetLong("这是一个红房间。概率实验室二在东边。");
    SetExits( ([
                "east" : "/domains/campus/room/plab2"
                ]) );
    SetDoor("east","/domains/campus/doors/red_door2");
}
void init(){
    ::init();
}
