#include <lib.h>

inherit LIB_DUMMY; // These do not show up in desc, but you can look at them
inherit LIB_PULL; // Makes the item pullable
inherit LIB_PRESS; // Makes the item pressable

int openDoor(object who) {
    object door1 = load_object("/domains/town/doors/welldoor1");
    object door2 = load_object("/domains/town/doors/welldoor2");
    if(!door1->GetClosed()){
        write("拉杆已经在拉起的位置了。");
    }
    else {
        write("你拉下拉杆，西边的门打开了。");
        say(this_player()->GetName()+"拉下拉杆，西边的门打开了。");
        tell_room("/domains/town/room/well2","东边的门打开了，西边的门关闭了。");
        tell_room("/domains/town/room/well3","东边的门关闭了。");
        door1->SetClosed(0);
        door2->SetClosed(1);
    }
    return 1;
}

int closeDoor(object who){
    object door1 = load_object("/domains/town/doors/welldoor1");
    object door2 = load_object("/domains/town/doors/welldoor2");
    if(door1->GetClosed()){
        write("拉杆已经在按下的位置了。");
    }
    else {
        write("你按下拉杆，西边的门关闭了。");
        say(this_player()->GetName()+"按下拉杆，西边的门关闭了。");
        tell_room("/domains/town/room/well2","东边的门关闭了，西边的门打开了。");
        tell_room("/domains/town/room/well3","东边的门打开了。");
        door1->SetClosed(1);
        door2->SetClosed(0);
    }
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
