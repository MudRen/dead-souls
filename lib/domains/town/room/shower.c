#include <lib.h>
inherit LIB_ROOM;
protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("淋浴间");
    SetLong("你站在一个淋浴间里。人们来这里清洁身体。");
    SetExits( ([
                "out" : "/domains/town/room/mansion_room3"
                ]) );
    SetObviousExits("out");
}

void init(){
    ::init();
}
