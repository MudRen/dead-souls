#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("chest");
    SetId(({"chest","wooden chest"}));
    SetShort("一个木箱");
    SetLong("这是一个结实的木箱，用于存放贵重物品。");
    SetMass(2000);
    SetBaseCost("silver",50);
    SetMaxCarry(1500);
    SetInventory(([
                "/secure/obj/memo" : 1,
                "/secure/obj/medtric" : 1,
                "/secure/obj/control" : 1,
                //"/secure/obj/roommaker" : 1,
                "/domains/town/armor/badge" : 1,
                ]));
    SetCanClose(1);
    SetClosed(1);
}

void init(){
    ::init();
}

mixed CanGet(object ob) { return "The chest does not budge.";}
