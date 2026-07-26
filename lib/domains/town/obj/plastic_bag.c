#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetId( ({ "bag" }) );
    SetAdjectives( ({ "small", "plastic", "a" }) );
    SetShort("一个小塑料袋");
    SetLong("这是一个用来装东西的简单塑料袋。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetMaxCarry(50);
    SetOpacity(0);
}

void init(){
    ::init();
}
