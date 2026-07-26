#include <lib.h>
#include <props.h>

inherit LIB_BED;

protected void create() {
    ::create();
    SetKeyName("guest bed");
    SetId( ({ "bed" }) );
    SetAdjectives( ({ "guest" }) );
    SetShort("一张客用床");
    SetLong("这是一张看起来很舒适的客用床。");
    SetMass(1000);
    SetBaseCost("silver",800);
    SetMaxSitters(2);
    SetMaxLiers(1);
}

void init(){
    ::init();
}
