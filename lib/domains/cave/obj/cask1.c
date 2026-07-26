#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("cask");
    SetId( ({"cask","keg"}) );
    SetAdjectives( ({"large","wooden","wood"}) );
    SetShort("一个木桶");
    SetLong("一个用来盛放液体的大型木桶。");
    SetMass(1000);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("water");
    SetFlaskUses(20);
    SetStrength(5);
    SetMaxFlask(50); 
    SetMealType(MEAL_DRINK);
    SetTapped(1);
}

void init(){
    ::init();
}
