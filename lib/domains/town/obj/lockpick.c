#include <lib.h>

inherit LIB_LOCKPICK;

void create(){
    lockpick::create();
    SetKeyName("lockpick");
    SetAdjectives(({"lockpicking","picking"}));
    SetId(({ "tool","pick" }));
    SetShort("一把开锁器");
    SetLong("一个开锁工具。");
    SetMass(1);
    SetBaseCost("silver", 10);
    SetPickingQuality(10);
}

void init(){
    ::init();
}
