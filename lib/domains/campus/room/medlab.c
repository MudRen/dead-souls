#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("医学研究实验室");
    SetLong("医学实验在此进行。");
    SetClimate("indoors");
    SetProperty("nopeer",1);
    SetItems( ([
                ({ "door","sliding door" }) : "一扇奇怪的金属滑动门。",
                ]) );
    SetExits( ([
                "north" : "/domains/campus/room/science5.c",
                ]) );
}

void init(){
    ::init();
}
