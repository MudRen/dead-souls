#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

int PreExit(mixed args...){
    object who = this_player();
    write("你被滑动门的一道光束扫描了。");
    say(who->GetName()+"被滑动门的一道光束扫描了。");
    if(!present_file("/domains/campus/armor/badge2",who)){
        write("门没有打开。");
        return 0;
    }
    else {
        write("门打开了，让你通过。\n");
        say("门让"+who->GetName()+"通过了。\n");
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
