#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("DIR_X", ([ "id" : ({"door leading DIR_X", "door", "DIR_X door"}),
                "short" : "通往DIR_X的门",
                "long" : "这是通往DIR_X的门的Y_SIDE面。",
                "lockable" : 1 ]) );

    SetSide("DIR_Y", ([ "id" : ({"door leading DIR_Y", "door", "DIR_Y door"}),
                "short" : "通往DIR_Y的门",
                "long" : "这是通往DIR_Y的门的X_SIDE面。",
                "lockable" : 1 ]) );

    SetClosed(1);
    SetLocked(0);
    SetKeys("DIR_X", ({ "DIR_X key" }));
    SetKeys("DIR_Y", ({ "DIR_Y key" }));
}

void init(){
    ::init();
}
