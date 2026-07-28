#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("javarin");
    SetId(({"pill","stimulant"}));
    SetShort("一片甲瓦林药片");
    SetAdjectives(({"javarin","small","yellow"}));
    SetLong("一粒黄色兴奋剂。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",1);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吞下一颗药丸。",
            "$N 吞下一颗药丸。");
    SetDuration(10);
    SetStats( ([ "speed" : 1 ]) );
    SetPoints( ([ "caffeine" : 20 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
