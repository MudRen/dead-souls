#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼走廊");
    SetLong("这是LPC大学科学楼，令人兴奋的新系统和抽象研究在此进行。南边是概率实验室。走廊向西延伸。大楼出口在北边，通往大学广场。");
    SetExits( ([ 
                "north" : "/domains/campus/room/usquare",
                "south" : "/domains/campus/room/wiz_lab",
                "west" : "/domains/campus/room/science2",
                ]) );
    SetClimate("indoors");

    SetDoor("south", "/domains/campus/doors/prob_door.c");

}
void init(){
    ::init();
}
