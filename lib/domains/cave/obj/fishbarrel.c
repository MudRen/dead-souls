#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("barrel");
    SetId( ({ "barrel" }) );
    SetAdjectives( ({ "simple","oak","oaken","wood","wooden" }) );
    SetShort("一个橡木桶");
    SetLong("这是一个用来存放东西的简易木桶。");
    SetMass(474);
    SetMaxCarry(500);
    SetInventory( ([
                "/domains/cave/meals/herring" : random(100),
                ]) );
}

void init(){
    ::init();
}
