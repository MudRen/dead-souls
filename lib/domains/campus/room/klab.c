#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("克莱纳储藏室");
    SetLong("这里显然是克莱纳博士存放大型研究设备的地方。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits(([
                "west" : "/domains/campus/room/kleiner",
                ]));
}

void init(){
    ::init();
}
