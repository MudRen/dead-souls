#include <lib.h>

inherit LIB_CHAIR;

protected void create() {
    chair::create();
    SetKeyName("chair");
    SetAdjectives( ({"simple", "wooden"}) );
    SetId("chair");
    SetShort("木椅");
    SetLong("一把简单的木椅，用来坐的。");
    SetMass(150);
    SetDollarCost(15);
    SetMaxSitters(1);
}

void init(){
    ::init();
}
