#include <lib.h>
#include <meal_types.h>
#include <dirs.h>

inherit LIB_FISH;

protected void create() {
    fish::create();
    SetKeyName("herring");
    SetId( ({ "fish" }) );
    SetAdjectives( ({ "red","saltwater","salt water" }) );
    SetShort("一条红鲱鱼");
    SetLong("这是一种咸水鱼，红色的。");
    SetMealType(MEAL_FOOD);
    SetMass(10); 
    SetStrength(10); 
    SetBaseCost("silver", 2);
    SetFight(4);
    SetFood("/domains/town/meals/herring");
}
void init(){
    ::init();
}
