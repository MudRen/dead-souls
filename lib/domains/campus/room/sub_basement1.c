#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(0);
    SetShort("地下层");
    SetLong("这是校园深处的地下室。地下室从这里向西延伸。东边有一个门口。");
    SetExits( ([
                "east" : "/domains/campus/room/maintenance",
                "west" : "/domains/campus/room/sub_basement2.c",
                ]) );
    SetInventory(([
                ]));
    SetDoor("east", "/domains/campus/doors/plain_door2");
    SetEnters( ([ 
                ]) );
}

void init(){
    ::init();
}
