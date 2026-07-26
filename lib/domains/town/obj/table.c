#include <lib.h>

inherit LIB_CHAIR;

void create() {
    chair::create();
    SetKeyName("wooden table");
    SetId( ({ "table" }) );
    SetAdjectives( ({ "wood","wooden", "simple", "medium-sized" "medium sized" }) );
    SetShort("一张木桌");
    SetLong("这是一张简单的中等大小的木桌。");
    SetInventory(([
                "/domains/default/obj/handbook" : 1,
                ]));
    SetMass(274);
    SetBaseCost("silver",1);
    SetBaseCost("silver",1);
    SetMaxCarry(5000);
    inventory_visible();
    inventory_accessible();
}

void init(){
    ::init();
}
