#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int PreExit(mixed args...){
    object who = this_player();
    write("You are scanned by a beam of light from the sliding door.");
    say(who->GetName()+" is scanned by a beam of light from the sliding door.");
    if(!present_file("/domains/campus/armor/badge2",who)){
        write("The door does not open.");
        return 0;
    }
    else {
        write("The door opens, letting you through.\n");
        say("The door lets "+who->GetName()+" through.\n");
        return 1;
    }
}

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("科学楼副走廊，西段");
    SetLong("这是LPC大学科学楼的副走廊。走廊从这里向东延伸。北边是一扇滑动门。西边是一扇电梯门。");
    SetClimate("indoors");
    SetItems( ([
                ({ "door","sliding door" }) : "一扇奇怪的金属滑动门。",
                ]) );
    SetExits( ([
                "south" : "/domains/campus/room/stairwell2a",
                "east" : "/domains/campus/room/science5",
                "west" : "/domains/campus/room/shaft1.c",
                ]) );
    AddExit("north", "/domains/campus/room/weaplab", (: PreExit :));
    SetDoor("west", "/domains/campus/doors/eledoor1");
}

void init(){
    ::init();
}
