#include <lib.h>

inherit LIB_ROOM;

protected void create() {

    room::create();
    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort("创造者的工作室");
    SetLong("你站在一个创造者的工作室里。起始房间在下面。");
    SetItems( ([
                "workroom" : "看起来非常不错。",
                ]) );
    SetInventory(([
                ]));
    SetObviousExits("down");
    SetExits( ([ "down" : "/domains/default/room/start.c",
                ]) );
}

