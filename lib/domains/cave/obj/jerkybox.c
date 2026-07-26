#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("box");
    SetId( ({ "box" }) );
    SetAdjectives( ({ "wooden","wood" }) );
    SetShort("一个木箱");
    SetLong("这是一个用来存放东西的木箱。");
    SetMass(274);
    SetMaxCarry(500);
    SetInventory( ([
                "/domains/cave/meals/jerky" : random(100)+1,
                ]) );
}

void init(){
    ::init();
}
