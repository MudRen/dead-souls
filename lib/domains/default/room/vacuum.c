#include <lib.h>
#include ROOMS_H
#include <respiration_types.h>

inherit LIB_ROOM;

void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("无空气房间");
    SetLong("这个房间的唯一目的就是没有任何可以呼吸的空气。");
    SetRespirationType(R_VACUUM);
}

void init(){
    ::init();
}
