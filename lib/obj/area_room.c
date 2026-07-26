#include <lib.h>
#include ROOMS_H

#include "../customdefs.h";

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("空房间");
    SetLong("一个毫无特色的区域。");
}

void init(){
    ::init();
}

