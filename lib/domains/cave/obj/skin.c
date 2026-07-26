#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("skin");
    SetId( ({"skin","vessel","bladder","pouch"}) );
    SetAdjectives( ({"skin","bladder","water","animal"}) );
    SetShort("一个水袋");
    SetLong("一个用动物膀胱制成的袋子，用来盛放液体。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("water");
    SetFlaskUses(20);
    SetStrength(5);
    SetMaxFlask(20); 
    SetMealType(MEAL_DRINK);
}

void init(){
    ::init();
}
