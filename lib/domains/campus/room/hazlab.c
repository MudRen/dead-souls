#include <lib.h>
#include ROOMS_H

inherit LIB_ROOM;

void create() {
    room::create();
    SetAmbientLight(30);
    SetShort("危险技术实验室");
    SetLong("大学的研究经常产生神秘、先进或外星的物品，可能对普通人构成危险。这个实验室就是对这些物品进行分析的地方。");
    SetInventory(([
                "/domains/campus/npc/turret" : 1,
                "/domains/campus/obj/workbench" : 1,
                "/domains/default/armor/pscoutsuit" : 1,
                ]));
    SetExits(([
                "north" : "/domains/campus/room/science2",
                ]));

    SetClimate("indoors");
    SetProperty("nopeer",1);
}
void init(){
    ::init();
}
