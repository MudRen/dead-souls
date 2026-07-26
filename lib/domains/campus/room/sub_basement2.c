#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("地下层");
    SetLong("这是校园深处的地下室。电梯在西边，楼梯间在南边。地下室向东延伸。");
    SetItems(([
                ]));
    SetExits( ([
                "east" : "/domains/campus/room/sub_basement1",
                "west" : "/domains/campus/room/shaftb",
                "south" : "/domains/campus/room/stairwell2d.c",
                ]) );
    SetInventory(([
                ]));

    SetEnters( ([ 
                ]) );
}

void init(){
    ::init();
}
