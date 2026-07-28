#include <lib.h>
#include <vendor_types.h>
#include <meal_types.h>
inherit LIB_FLASK;

void create(){
    ::create();
    SetKeyName("lister bag");
    SetId( ({"lister","bag","tripod"}) );
    SetAdjectives( ({"large","canvas","wood","suspended"}) );
    SetShort("一个水袋");
    SetLong("一个挂在三脚架上的大型帆布水袋，里面装着饮用水。");
    SetMass(2000);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
    SetFlaskContents("water");
    SetFlaskUses(1000);
    SetStrength(5);
    SetMaxFlask(1000); 
    SetMealType(MEAL_DRINK);
    SetTapped(1);
    SetPreventGet("这个装置无法移动。");
}

void init(){
    ::init();
}

mixed CanDrink(object who, string what){
    return "这是一个带龙头的"+GetKeyName()+"。你应该用容器接水喝，而不是直接对着喝，野蛮人。";
}
