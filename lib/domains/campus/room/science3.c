#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼走廊，西端");
    SetLong("这是LPC大学科学楼主走廊的西端。主走廊从这里向东延伸，通往大楼出口。另一条走廊从这里向南延伸。");
    SetClimate("indoors");
    SetItems( ([ 
                ]) );
    SetExits( ([
                "east" : "/domains/campus/room/science2",
                "south" : "/domains/campus/room/science4.c",
                ]) );
}

void init(){
    ::init();
}
