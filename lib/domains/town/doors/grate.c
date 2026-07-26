#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("down", ([ "id" : ({"grate leading down", "grate", "down grate"}),
                "short" : "a grate leading down",
                "long" : "这是一个通往下方的格栅的上侧。看起来非常沉重。",
                "lockable" : 0 ]) );

    SetSide("up", ([ "id" : ({"grate leading up", "grate", "up grate"}),
                "short" : "a grate leading up",
                "long" : "这是一个通往上方的格栅的下侧。看起来非常沉重。",
                "lockable" : 0 ]) );

    SetPerforated(1);
    SetClosed(1);
    SetLocked(0);
}

varargs mixed CanOpen(object ob, string id){
    mixed ret = ::CanOpen(ob, id);
    if(!ret || !intp(ret)) return ret;
    if(ob->GetStatLevel("strength") > 49){
        return 1;
    }
    else {
        write("你的体力不够！");
        return 0;
    }
}

void init(){
    ::init();
}
