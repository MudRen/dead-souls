#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("初始舱");
    SetLong("初始舱。一些物品会在这里被创建和识别。向下走可以离开。");
    SetExits( ([ "down" : ROOM_START ]) );
}
int CanReceive(object ob){
    return room::CanReceive(ob);
}
