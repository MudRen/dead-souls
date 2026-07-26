#include <lib.h>
#include "../customdefs.h"

inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("第二示例房间");
    SetLong("这是另一个示例房间。");
    SetItems( ([
                "template" : "这就是模板。",
                ]) );
    SetInventory(([
                MY_OBJ "/case" :1,
                ]));
    SetExits(([
                "west" : MY_AREA "/room/sample_room",
                ]));

}

void init(){
    ::init();
}
