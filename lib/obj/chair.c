#include <lib.h>

inherit LIB_CHAIR;


protected void create() {
    chair::create();
    SetKeyName("chair");
    SetId("chair");
    SetAdjectives( ({ "generic","nondescript" }) );
    SetShort("普通椅子");
    SetLong("一把不起眼的椅子。");
    SetMass(150);
    SetDollarCost(15);
    SetMaxSitters(1);
}
void init(){
    ::init();
}
