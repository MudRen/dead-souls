#include <lib.h>

inherit LIB_TABLE;

void create() {
    ::create();
    SetKeyName("wooden table");
    SetId( ({ "table" }) );
    SetAdjectives( ({ "wood","wooden", "simple", "medium-sized" "medium sized" }) );
    SetShort("一张木桌");
    SetLong("这是一张简单的中等大小木桌。");
    SetInventory(([
                ]));
    SetMass(274);
    SetBaseCost("silver",1);
    SetBaseCost("silver",1);
    SetMaxCarry(500);
}

void init(){
    ::init();
}
