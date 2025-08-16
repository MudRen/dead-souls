#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("楼上浴室");
    SetLong("你在浴室里。对于如此宏伟的公馆来说，这里相当普通，"
            "但看起来功能齐全且基本干净。这里有一个淋浴间"
            "你可以进入。");
    SetItems( ([
                ({"stall","shower stall","shower" })  : "一个淋浴间。",
                ({"sink","bathroom sink" })  : "一个普通的水槽。",
                ]) );
    SetExits( ([
                "west" : "/domains/town/room/mansion_uhall2"
                ]) );
    SetInventory( ([
                "/domains/town/obj/toilet" : 1,
                "/domains/town/obj/mat" : 1
                ]) );
    SetEnters( ([
                "stall" : "/domains/town/room/shower",
                "shower stall" : "/domains/town/room/shower",
                "shower" : "/domains/town/room/shower"
                ]) );

    SetDoor("west", "/domains/town/doors/m3.c");

}
void init(){
    ::init();
}
