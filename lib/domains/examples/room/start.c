#include <lib.h>
#include ROOMS_H
#include "ex.h"

inherit LIB_ROOM;


void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("空白房间");
    SetLong("一个平淡无奇的区域。示例房间在北边。");
    SetExits( ([
                "north" : EXPATH + "entrance"
                ]) );
    SetCoordinates("-3000,-3000,-3000");
}
void init(){
    ::init();
}
