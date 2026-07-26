#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("hamburger");
    SetId(({"hamburger","burger"}));
    SetShort("油腻的汉堡包");
    SetLong("显然有些人认为这是食物，这个夹在面包里的小怪物又油腻、又扁平，还有点发灰。请享用！");
    SetNoCondition(1);
    SetMass(15);
    SetStrength(35);
    //SetDollarCost(4);
    SetDollarCost(4);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You wolf down your hamburger with gusto.",
            "$N wolfs down $P hamburger hungrily.");
}
void init(){
    ::init();
}
