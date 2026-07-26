#include <lib.h>

inherit LIB_DOOR;

protected void create() {
    door::create();

    SetSide("east", ([ "id" : ({"pressure door leading east", "door", "pressure door", "east door"}),
                "short" : "a pressure door leading east",
                "long" : "这是通往东方的气压门的西侧。它巨大而沉重，设计用来承受和抵御巨大的水压。",
                "lockable" : 1 ]) );

    SetSide("west", ([ "id" : ({"pressure door leading west", "door", "pressure door", "west door"}),
                "short" : "a pressure door leading west",
                "long" : "这是通往西方的气压门的东侧。它巨大而沉重，设计用来承受和抵御巨大的水压。",
                "lockable" : 1 ]) );

    SetClosed(1);
    SetLocked(1);
    SetKeys("east", ({ "lab key" }));
    SetKeys("west", ({ "lab key" }));
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

varargs mixed CanClose(object who, string id){
    mixed ret = ::CanClose(who, id);
    if(!ret || !intp(ret)) return ret;
    if(who->GetStatLevel("strength") > 49){
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
