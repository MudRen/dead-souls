#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("mug");
    SetId( ({"mug", "mug made of clay"}) );
    SetAdjectives( ({"simple","clay"}) );
    SetShort("一个陶杯");
    SetLong("一个简单的陶制杯子，用来盛放液体。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetVendorType(VT_TREASURE);
    SetFlaskUses(0);
    SetStrength(5);
    SetMaxFlask(2); 
    SetMealType(MEAL_DRINK);
}
void init(){
    ::init();
}
