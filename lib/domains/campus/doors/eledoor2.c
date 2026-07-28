#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("east", (["id" : ({ "door", "elevator door" }),
                "short" : "一扇通向东方的电梯门",
                "long" : "这是一扇电梯门。",
                "lockable" : 0 ]) );
    SetSide("west", (["id" : ({ "door", "elevator door" }),
                "short" : "一扇通向西方的电梯门",
                "long" : "这是一扇电梯门。",
                "lockable" : 0 ]) );
    SetClosed(1);
    SetLocked(0);
}

void init(){
    ::init();
}
mixed CanOpen(object ob){
    return "没有把手可以打开它。";
}
