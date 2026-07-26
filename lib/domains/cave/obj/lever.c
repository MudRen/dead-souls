#include <lib.h>
#include <medium.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PULL; // Makes the item pullable
inherit LIB_PRESS; // Makes the item pressable

private nosave int Sprung = 0;
object chiefroom = load_object("/domains/cave/room/chieftain");

int GetSprung(){
    if(Sprung) return 1;
    return 0;
}

int openDoor(object who) {
    if(GetSprung()){
        write("拉杆已经处于拉动位置了。");
    }
    else {
        object *inv = ( all_inventory(chiefroom) - ({ this_object() }) );
        write("你拉动了拉杆，地板塌陷了！");
        say(this_player()->GetName()+" pulls the lever, and the floor drops out!");
        tell_room("/domains/cave/room/cavetroll","天花板打开了。");
        chiefroom->SetMedium(MEDIUM_AIR);
        chiefroom->AddExit("down","/domains/cave/room/cavetroll");
        inv->eventCheckEnvironment();
        filter(inv,(: !living($1) :))->eventFall();
    }
    Sprung = 1;
    return 1;
}

int closeDoor(object who){
    if(!GetSprung()){
        write("拉杆已经处于推动位置了。");
    }
    else {
        write("你推动了拉杆，地板合上了。");
        say(this_player()->GetName()+" pushes the lever, and the floor closes.");
        tell_room("/domains/cave/room/cavetroll","天花板关闭了。");
        chiefroom->SetMedium(MEDIUM_LAND);
        chiefroom->RemoveExit("down");
    }
    Sprung = 0;
    return 1;
}

protected void create() {
    dummy::create();
    SetKeyName("lever");
    SetId(({"lever","lever on the wall" }));
    SetAdjectives("wooden");
    SetShort("一根拉杆");
    SetLong("这是一根拉杆。");
    SetPress((: closeDoor :));
    SetPull((: openDoor :));
}
