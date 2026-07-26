#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼楼梯间，底部");
    SetLong("这是大学科学楼楼梯间的底部。楼梯从这里向上延伸。楼梯下面有一个爬行空间。地下层在北边。");
    SetItems(([
                ({ "stairs", "stair" }) : "向上的台阶。",
                "crawlspace" : "楼梯下的爬行空间。",
                ]));
    SetEnters( ([
                "crawlspace" : "/domains/campus/room/crawlspace2.c",
                ]) );
    SetClimate("indoors");
    SetExits( ([
                "up" : "/domains/campus/room/stairwell2c",
                "north" : "/domains/campus/room/sub_basement2.c",
                ]) );
}

void init(){
    ::init();
}
