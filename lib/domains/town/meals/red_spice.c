#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("red spice");
    SetId(({"spice","stick","stick of red spice","slender"}));
    SetShort("一根红色香料");
    SetAdjectives(({"red","spice"}));
    SetLong("一根细长的红色香料。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",8);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃了一根红色香料。",
            "$N 吃了一根红色香料。");
    SetDuration(1);
    SetPoints( ([ "HP" : 300 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
