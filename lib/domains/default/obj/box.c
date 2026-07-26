#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("box");
    SetId( ({ "box" }) );
    SetAdjectives( ({ "small", "plastic","green", "a" }) );
    SetShort("一个小塑料盒");
    SetLong="a small plastic box";
    SetLong("这是一个 simple plastic box used to hold things。");
    SetMass(274);
    SetMaxCarry(500);
}
