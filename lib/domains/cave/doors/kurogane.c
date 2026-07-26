#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("north", ([ "id" : ({"door leading north", "door", "north door"}),
                "short" : "一扇通往北边的门",
                "long" : "这是一扇通往北边的门的南侧。",
                "lockable" : 1 ]) );

    SetSide("south", ([ "id" : ({"door leading south", "door", "south door"}),
                "short" : "一扇通往南边的门",
                "long" : "这是一扇通往南边的门的北侧。",
                "lockable" : 1 ]) );

    SetClosed(1);
    SetLocked(0);
    SetKeys("north", ({ "north key" }));
    SetKeys("south", ({ "south key" }));
}

void init(){
    ::init();
}
