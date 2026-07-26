#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetId( ({ "medical bag" }) );
    SetAdjectives( ({ "small", "cloth", "a" }) );
    SetShort("一个小布袋");
    SetLong("这是一个用来装东西的简单布袋。上面印着：红十字会");
    SetMass(30);
    SetBaseCost("silver",5);
    SetMaxCarry(300);
}

void init(){
    ::init();
}
