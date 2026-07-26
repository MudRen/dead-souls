#include <lib.h>
inherit LIB_ROOM;

protected void create() {
    room::create();
    SetClimate("outdoors");
    SetAmbientLight(30);
    SetNightLight(10);
    SetDayLight(30);
    SetShort("兽人山谷");
    SetLong("你在西边陡峭悬崖下方的一个小山谷里。一群兽人似乎已经把这里当成了家，你可以看到北边他们摇摇欲坠的堡垒。一条繁忙的小径向东通往森林，一条狭窄的小径蜿蜒向西南进入树林。");
    SetSkyDomain("town");
    SetExits( ([
                "east" : "/domains/town/room/clearing",
                "north" : "/domains/town/room/orc_fortress",
                "southwest" : "/domains/town/room/narrow_path.c",
                ]) );
    SetInventory(([
                "/domains/town/npc/orc" : 1,
                "/domains/town/npc/orc2" : 1,
                ]) );
}

void init(){
    ::init();
}

int clean_up(int ref_exists){
    return ::clean_up();
}

void reset(){
}
