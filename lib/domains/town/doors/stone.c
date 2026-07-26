#include <lib.h>

inherit LIB_DOOR;
//inherit LIB_READ;
//inherit LIB_LOOK;

protected void create() {
    door::create();

    SetSide("north", ([ "id" : ({"door leading north", "door", "north door", "stone door"}),
                "short" : "a stone door leading north",
                "long" : "这是通往北方的石门的南侧。它太沉重了，无法用常规手段打开或关闭。门上有一段铭文。",
                "lockable" : 0 ]) );

    SetSide("south", ([ "id" : ({"door leading south", "door", "south door", "stone door"}),
                "short" : "a stone door leading south",
                "long" : "这是通往南方的石门的北侧。它太沉重了，无法用常规手段打开或关闭。",
                "lockable" : 0 ]) );
    SetClosed(1);
    SetLocked(0);
}

varargs int eventOpen(object who, object tool) {
    object room;
    string tmp;

    room = environment(who);
    who->eventPrint("你未能打开" + GetShort(tmp) + "。");
    room->eventPrint(who->GetName() + " 未能打开" + GetShort(tmp) + "。",
            who);
    return 0;
}

varargs mixed eventClose(object who){
    object room;
    string tmp;

    room = environment(who);
    who->eventPrint("你未能关闭" + GetShort(tmp) + "。");
    room->eventPrint(who->GetName() + " 未能关闭" + GetShort(tmp) + "。",
            who);
    return 0;
}

void init(){
    ::init();
}
