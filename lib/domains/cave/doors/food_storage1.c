#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("south", (["id" : ({ "door leading south", "door", "south door" }),
                "short" : "一扇通往南边的门",
                "long" : "这是一扇通往南边的门的北侧。",
                "lockable" : 1 ]) );
    SetKeys("south", ({ "food_storage_one" }));

    SetSide("north", (["id" : ({ "door leading north", "door", "north door" }),
                "short" : "一扇通往北边的门",
                "long" : "这是一扇通往北边的门的南侧。",
                "lockable" : 1 ]) );
    SetKeys("north", ({ "food_storage_one" }));

    SetClosed(1);
    SetLocked(1);
}
