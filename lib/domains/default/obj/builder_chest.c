#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetId(({"chest","wooden chest"}));
    SetShort("一个木箱");
    SetLong("这是一个坚固的木箱，用于存放贵重物品。");
    SetInventory(([
                "/domains/town/armor/collar" : 1,
                "/domains/default/obj/bguide" : 1,
                "/secure/obj/machine" : 1,
                "/domains/default/obj/meter" : 1,
                "/secure/obj/control" : 1,
                "/secure/obj/memo" : 1,
                "/secure/obj/staff" : 1,
                "/domains/default/obj/pinger" : 1,
                "/secure/obj/medtric" : 1,
                ]));
    SetMass(2000);
    SetBaseCost(50);
    SetMaxCarry(10000);
    SetPreventPut("你不能把这个放进去！");
    SetPreventGet("这个箱子纹丝不动。");
    SetCanClose(1);
    SetClosed(1);
}

void init(){
    ::init();
}
