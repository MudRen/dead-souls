#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("厨房");
    SetLong("这是一个非常大的厨房，设计用来"
            "容纳数十名厨师。看起来已经很久"
            "没有人在这里做饭了。");
    SetExits( ([
                "west" : "/domains/town/room/mansion_dhall2.c",
                ]) );
    SetInventory( ([
                "/domains/town/obj/rack" : 1,
                "/domains/town/obj/stove" : 1,
                "/domains/town/npc/rat" : (: random(5)+1 :) ,
                ]) );
}

void init(){
    room::init();
}
