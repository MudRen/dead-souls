#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("crate");
    SetId( ({ "crate" }) );
    SetAdjectives( ({ "large", "wooden","wood" }) );
    SetShort("一个大木箱");
    SetLong("这是一个用来存放东西的大木箱。");
    SetMass(374);
    SetMaxCarry(700);
    SetInventory( ([
                "/domains/cave/meals/jerky" : random(350)+1,
                ]) );
}

void init(){
    ::init();
}
