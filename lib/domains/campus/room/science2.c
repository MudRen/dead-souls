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
    SetShort("科学楼走廊");
    SetLong("这是LPC大学科学楼的主走廊。走廊从这里向东西延伸。南边是一扇滑动门。北边是星门实验室。");
    SetClimate("indoors");
    SetItems( ([
                ({ "door","sliding door" }) : "一扇奇怪的金属滑动门。",
                ]) );
    SetExits( ([
                "north" : "/domains/campus/room/slab",
                "east" : "/domains/campus/room/science1",
                "west" : "/domains/campus/room/science3.c",
                ]) );
    AddExit("south", "/domains/campus/room/hazlab", (: PreExit :));
}
void init(){
    ::init();
}
