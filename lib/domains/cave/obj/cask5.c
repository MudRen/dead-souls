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
    SetMass(2000);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("grog");
    SetFlaskUses(1000);
    SetStrength(5);
    SetMaxFlask(1000); 
    SetMealType(MEAL_ALCOHOL);
    SetTapped(1);
    SetPreventGet("木桶固定在地上。");
}

void init(){
    ::init();
}

mixed CanDrink(object who, string what){
    return "这是一个带龙头的"+GetKeyName()+"。你应该用容器接酒喝，而不是直接对着喝，野蛮人。";
}

