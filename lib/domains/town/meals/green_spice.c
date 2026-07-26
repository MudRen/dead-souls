#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("green spice");
    SetId(({"spice","stick","stick of green spice","slender"}));
    SetShort("一根绿色香料");
    SetAdjectives(({"green","spice"}));
    SetLong("一根细长的绿色香料。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",12);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You eat a stick of green spice.",
            "$N eats a stick of green spice.");
    SetDuration(60);
    SetStats( ([ "durability" : 1 ]) );
    SetPoints( ([ "HP" : 650 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
