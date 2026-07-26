#include <lib.h>
#include <climb.h> // defines CLIMB_DOWN

inherit LIB_ITEM;
inherit LIB_CLIMB;

protected void create() {
    ::create();
    SetKeyName("ladder");
    SetId("ladder");
    SetAdjectives(({"short","wood","wooden"}));
    SetShort("一个梯子");
    SetLong("这是一把标准的木梯，适合攀爬。");
    SetMass(100);
    SetBaseCost("silver",10);
}

void init(){
    ::init();
}
