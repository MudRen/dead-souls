#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("学习中心起点");
    SetLong("在这里你可以开始学习如何与你连接的虚拟世界进行互动。\n\n要开始教程，请输入：tutorial\n\n要返回正常区域，请输入：normal\n");
    SetCoordinates("2000,2000,0");
    SetNoObviousExits(1);
    SetNoClean(1);
}
void init(){
    ::init();
}
