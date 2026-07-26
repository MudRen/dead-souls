#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("apple");
    SetId(({"fruit"}));
    SetAdjectives( ({ "fresh","tasty","tasy-looking","red"}) );
    SetShort("一个苹果");
    SetLong("这是一个新鲜的、红色的、看起来很好吃的苹果。");
    SetMass(5);
    SetStrength(35);
    SetDollarCost(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("You wolf down your apple with gusto.",
            "$N wolfs down $P apple hungrily.");
}
void init(){
    ::init();
}
