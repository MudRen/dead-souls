#include <lib.h>
#include "../customdefs.h"

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("示例房间");
    SetLong("这是一个可以用作模板的房间。");
    SetItems( ([
                "template" : "这就是模板。",
                ]) );
    SetExits( ([
                "west" : MY_DIR "/workroom",
                "east" : MY_ROOM "/sample_two.c",
                ]) );
    SetInventory( ([
                MY_OBJ "/table" : 1,
                MY_NPC "/fighter" : 1,
                ]) );
}

void init(){
    ::init();
}
