#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("speedalin");
    SetId(({"pill","stimulant"}));
    SetShort("一片斯必得林药片");
    SetAdjectives(({"speedalin","small","white"}));
    SetLong("一粒白色兴奋剂。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",2);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You swallow a pill.",
            "$N swallows a pill.");
    SetDuration(20);
    SetStats( ([ "speed" : 1 ]) );
    SetPoints( ([ "caffeine" : 30 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
