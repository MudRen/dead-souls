#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("flask");
    SetId( ({"flask"}) );
    SetAdjectives( ({"small","metal","vessel"}) );
    SetShort("一个小瓶子");
    SetLong("一个小的金属容器，用来装液体。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("water");
    SetFlaskUses(2);
    SetStrength(5);
    SetMaxFlask(3); 
    SetMealType(MEAL_DRINK);
}

void init(){
    ::init();
}
