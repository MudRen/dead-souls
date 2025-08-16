#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(5);
    SetShort("黑暗洞穴");
    SetLong("这是悬崖底部的一个小洞穴。南墙上有一扇石门。");
    SetClimate("indoors");
    SetInventory(([
                "/domains/town/weap/fellsword" : 1,
                "/domains/town/obj/scroll_resurrection" : 1,
                ]));
    SetExits(([
                "south" : "/domains/town/room/cave_entrance",
                ]));

    SetDoor("south", "/domains/town/doors/stone.c");

}
void init(){
    ::init();
}
