#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    ::create();
    SetAmbientLight(5);
    SetNightLight(15);
    SetDayLight(25);
    SetShort("黑暗洞穴");
    SetNightLong("这是一个位于粗糙石壁山体中的洞穴。"+
            "洞穴向南敞开，通向夜色。北面是一片黑暗。");
    SetDayLong("这是一个位于粗糙石壁山体中的洞穴。日光从南面照入，那里有一片森林。北面，洞穴继续延伸向黑暗之中。");
    SetLong("这是森林附近的一个小洞穴。");
    SetItems(([
                ({ "wall", "rocky wall", "mountain wall", "rough stone mountain wall", "stone mountain wall" }) : "地质活动在漫长岁月中形成了这个洞穴，但显然有智慧生物将其改造成了适合居住的大小和形状。",
                ]));
    SetInventory(([
                "/domains/town/obj/ladder" : 1,
                ]));
    SetExits( ([
                "south" : "/domains/town/virtual/forest/-3,25",
                "north" : "/domains/amigara/room/midair.c",
                ]) );
}
void init(){
    ::init();
}
