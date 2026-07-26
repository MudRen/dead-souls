#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>

inherit LIB_POTION;

protected void create() {
    potion::create();
    SetKeyName("potion");
    SetId( ({ "bottle", "potion","philtrum","potion of healing","potion of greater healing" }) );
    SetAdjectives(({"green", "healing","greater healing"}));
    SetShort("一瓶绿色强效治疗药水");
    SetLong("一瓶绿色液体，具有恢复大量生命值的魔法属性。");
    SetMass(60);
    SetMealType(MEAL_DRINK);
    SetStrength(15);
    SetMealMessages("You drink a potion.",
            "$N drinks a potion.");
    SetBaseCost("silver",5500);
    SetPoints( ([ "HP" : 1000 ]) );
    SetVendorType(VT_MAGIC);
}
void init(){
    ::init();
}
