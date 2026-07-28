#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();
    SetSide("down", ([ "id" : ({"service hatch", "hatch"}),
                "short" : "一个舱口",
                "long" : "这是一个检修舱口。",
                "lockable" : 0 ]) );
    SetSide("up", ([ "id" : ({"service hatch", "hatch"}),
                "short" : "一个舱口",
                "long" : "这是一个检修舱口。",
                "lockable" : 0 ]) );
    SetClosed(1);
}

mixed CanOpen(object ob){
    if(base_name(environment(ob)) == "/domains/campus/room/maintenance"){
        return 1;
    }
    else return "这边没有把手。";
}
