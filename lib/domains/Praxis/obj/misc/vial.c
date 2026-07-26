#include <lib.h>
#include <vendor_types.h>
inherit LIB_MEAL_POISON;
inherit LIB_MEAL;

void create() {
    meal::create();
    poison::create();
    SetKeyName("vial");
    SetId( ({ "vial", "vial of poison", "poison" }) );
    SetShort( "一瓶毒药");
    SetLong( "一个上面画着骷髅和交叉骨的玻璃瓶。");
    SetPoisonStrength(8);
    SetVendorType(VT_HERB);
    SetValue( 150);
    SetMass( 70);

}
