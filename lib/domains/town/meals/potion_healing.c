#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>

inherit LIB_POTION;

protected void create() {
    potion::create();
    SetKeyName("potion");
    SetId( ({ "bottle", "potion","philtrum","potion of healing","potion of minor healing" }) );
    SetAdjectives( "green", "healing","minor healing" );
    SetShort("一瓶绿色初级治疗药水");
    SetLong("一瓶绿色液体，具有恢复一些生命值的魔法属性。");
    SetMass(60);
    SetMealType(MEAL_DRINK);
    SetStrength(5);
    SetMealMessages("You drink a potion.",
            "$N drinks a potion.");
    SetBaseCost("silver",500);
    SetPoints( ([ "HP" : 100 ]) );
    SetVendorType(VT_MAGIC);
}
void init(){
    ::init();
}
