#include <lib.h>
#include ROOMS_H
#include <meal_types.h>
#include <vendor_types.h>

inherit LIB_POTION;

protected void create() {
    ::create();
    SetKeyName("spazalin");
    SetId(({"pill","stimulant"}));
    SetShort("一片斯帕扎林药片");
    SetAdjectives(({"spazalin","small","red"}));
    SetLong("一粒红色兴奋剂。");
    SetMass(1);
    SetStrength(1);
    SetBaseCost("gold",3);
    SetStrength(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吞下一颗药丸。",
            "$N 吞下一颗药丸。");
    SetDuration(60);
    SetStats( ([ "speed" : 1 ]) );
    SetPoints( ([ "caffeine" : 40 ]) );
    SetVendorType(VT_MAGIC);
}

void init(){
    ::init();
}
