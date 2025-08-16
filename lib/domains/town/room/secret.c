#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("秘密储藏室");
    SetLong("这似乎是一个用来保存贵重物品的秘密房间。"+
            "主卧室在西边。");
    SetExits( ([ "west" : "/domains/town/room/mansion_mbdroom" ]) );
    SetNoClean(1);
    SetPersistent(1);
    RestoreObject();
}

void init(){
    ::init();
}
