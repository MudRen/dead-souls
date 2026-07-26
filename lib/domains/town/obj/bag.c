#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("bag");
    SetAdjectives( ({"small", "cloth"}) );
    SetId( ({ "bag" }) );
    SetShort("一个小布袋");
    SetLong("这是一个用来装东西的简单布袋。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetMaxCarry(50);
}
void init(){
    ::init();
}
