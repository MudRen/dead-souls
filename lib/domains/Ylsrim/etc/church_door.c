#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("north", (["id" : ({ "door", "handsome wooden door", "wooden door" }),
                "short" : "一扇通往北边的门",
                "long" : "这是一扇普通的木门。",
                "lockable" : 1 ]) );

    SetSide("south", (["id" : ({ "door leading into the mansion", "handsome wooden door", "wooden door", "door" }),
                "short" : "一扇通往南边的门",
                "long" : "这是一扇漂亮的木门。",
                "lockable" : 1 ]) );

    SetClosed(1);
    SetLocked(1);
}
void init(){
    ::init();
}
