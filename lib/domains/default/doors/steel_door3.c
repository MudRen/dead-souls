#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("north", (["id" : ({ "steel door", "steel door leading north", "door", "north door" }),
                "short" : "一扇向北的钢门",
                "long" : "这是一扇 imposing, large steel door leading north into the arena。",
                "lockable" : 0 ]) );
    SetSide("south", (["id" : ({ "steel door", "steel door leading south", "south door", "door" }),
                "short" : "一扇向南的钢门",
                "long" : "这是一扇 imposing, large steel door leading south, out of the arena。",
                "lockable" : 0 ]) );

    SetClosed(0);
    SetLocked(0);
}
void init(){
    ::init();
}
