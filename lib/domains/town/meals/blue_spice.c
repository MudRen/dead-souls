#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("blue spice");
    SetId(({"spice","stick","stick of blue spice","slender"}));
    SetShort("一根蓝色香料");
    SetAdjectives(({"blue","spice"}));
    SetLong("一根细长的蓝色香料。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",10);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃了一根蓝色香料。",
            "$N 吃了一根蓝色香料。");
    SetDuration(30);
    SetStats( ([ "durability" : 1 ]) );
    SetPoints( ([ "HP" : 450 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
