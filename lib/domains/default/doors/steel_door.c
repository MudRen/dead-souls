#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("east", (["id" : ({ "steel door", "steel door leading east", "door", "east door" }),
                "short" : "一扇向东的钢门",
                "long" : "这是一扇 imposing, large steel door leading east into the arena。",
                "lockable" : 0 ]) );
    SetSide("west", (["id" : ({ "steel door", "steel door leading west", "west door", "door" }),
                "short" : "一扇向西的钢门",
                "long" : "这是一扇 imposing, large steel door leading west, out of the arena。",
                "lockable" : 0 ]) );

    SetClosed(0);
    SetLocked(0);
}
void init(){
    ::init();
}
