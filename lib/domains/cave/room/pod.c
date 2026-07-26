#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(30);
    SetShort("初始舱");
    SetLong("初始舱。一些物品在这里被创建和识别。往下走可以出去。");
    SetExits( ([ "down" : ROOM_START ]) );
}
int CanReceive(object ob){
    return ::CanReceive(ob);
}
