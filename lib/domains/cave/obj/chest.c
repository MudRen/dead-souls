#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetAdjectives(({"wooden","heavy"}));
    SetId(({"chest"}));
    SetShort("一个木箱");
    SetLong("这是一个沉重的木箱，用来存放物品。");
    SetInventory(([
                "/domains/cave/obj/letter2" : 1,
                "/domains/cave/armor/pajamas" : 1,
                "/domains/cave/obj/food_storage1_key" : 1,
                "/domains/cave/obj/letter3" : 1,
                ]));
    SetMass(2000);
    SetBaseCost("silver",50);
    SetMaxCarry(500);
    SetCanClose(1);
    SetClosed(1);
}

void init(){
    ::init();
}
