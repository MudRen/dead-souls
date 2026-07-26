#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("canteen");
    SetId( ({"canteen","vessel"}) );
    SetAdjectives( ({"plastic","green"}) );
    SetShort("一个绿色塑料水壶");
    SetLong("一个装液体的塑料容器。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("water");
    SetFlaskUses(10);
    SetStrength(5);
    SetMaxFlask(10); 
    SetMealType(MEAL_DRINK);
}
void init(){
    ::init();
}
