#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("east", ([ "id" : ({"door leading east", "door", "east door"}),
                "short" : "a door leading east",
                "long" : "这是通往东方的门的西侧。",
                "lockable" : 1 ]) );

    SetSide("west", ([ "id" : ({"door leading west", "door", "west door"}),
                "short" : "a door leading west",
                "long" : "这是通往西方的门的东侧。",
                "lockable" : 1 ]) );

    SetClosed(1);
    SetLocked(0);
    SetKeys("east", ({ "east key" }));
    SetKeys("west", ({ "west key" }));
}

void init(){
    ::init();
}

varargs int eventOpen(object who, object tool) {
    if(!this_object()->GetClosed()){
        write("它已经是开着的了。");
    }
    else {
        write("这扇门没有把手或其他可见的打开方式。");
    }
    return 1;
}

varargs int eventClose(object who) {
    if(this_object()->GetClosed()){
        write("它已经是开着的了。");
    }
    else {
        write("这扇门没有把手或其他可见的关闭方式。");
    }
    return 1;
}

