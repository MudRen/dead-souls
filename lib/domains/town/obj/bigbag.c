#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetId( ({ "bag" }) );
    SetAdjectives( ({ "giant", "cloth", "a" }) );
    SetShort("一个巨大的布袋");
    SetLong("这是一个用来装东西的简单布袋。");
    SetMass(100);
    SetBaseCost("silver",1);
    SetMaxCarry(2000);
}

void init(){
    ::init();
}
