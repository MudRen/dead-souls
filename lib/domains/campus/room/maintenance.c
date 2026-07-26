#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("维修间");
    SetLong("一个用于进入服务区域和存放维修物资的房间。");
    SetItems(([
                ]));
    SetInventory(([
                "/domains/campus/obj/simple_chair" : 1,
                "/domains/campus/obj/mtable" : 1,
                "/domains/campus/obj/mlocker" : 1,
                ]));
    SetExits( ([
                "up" : "/domains/campus/room/access9",
                "west" : "/domains/campus/room/sub_basement1.c",
                ]) );
    SetEnters( ([ 
                ]) );
    SetDoor("up", "/domains/campus/doors/hatch");
    SetDoor("west", "/domains/campus/doors/plain_door2");
}

void init(){
    ::init();
}
