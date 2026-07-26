#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>

inherit LIB_POTION;

protected void create() {
    potion::create();
    SetKeyName("potion");
    SetId( ({ "bottle", "potion","philtrum","potion of strength" }) );
    SetAdjectives( "red", "strength", "strongitude", "strongicity" );
    SetShort("一瓶红色力量药水");
    SetLong("一瓶红色液体，具有使人更强壮的魔法属性。");
    SetMass(60);
    SetMealType(MEAL_DRINK);
    SetStrength(5);
    SetMealMessages("You drink a potion.",
            "$N drinks a potion.");
    SetBaseCost("silver",1000);
    SetDuration(300);
    SetStats( ([ "strength" : 10 ]) );
    SetPoints( ([ "HP" : 50, "SP" : 50 ]) );
    SetVendorType(VT_MAGIC);
}
void init(){
    ::init();
}
