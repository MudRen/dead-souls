#include <lib.h>
#include ROOMS_H

inherit "/domains/cave/etc/cave_room";

void create() {
    ::create();
    SetAmbientLight(30);
    SetShort("空白房间");
    SetLong("一个没有任何特征的区域。");
}
void init(){
    ::init();
}
