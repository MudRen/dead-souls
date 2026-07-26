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
    SetShort("科学楼副走廊，东段");
    SetLong("这是LPC大学科学楼的副走廊。走廊从这里向东西延伸。南边是一扇滑动门。北边是一间教室。");
    SetClimate("indoors");
    SetItems( ([
                ({ "door","sliding door" }) : "一扇奇怪的金属滑动门。",
                ]) );
    SetExits( ([
                "north" : "/domains/campus/room/classroom1",
                "east" : "/domains/campus/room/science4",
                "west" : "/domains/campus/room/science6",
                ]) );
    AddExit("south", "/domains/campus/room/medlab", (: PreExit :));
}
void init(){
    ::init();
}
