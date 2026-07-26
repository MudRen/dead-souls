#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("bad apple");
    SetId(({"fruit","apple"}));
    SetAdjectives( ({ "foul","yucky","rotten-looking","browned","rotten"}) );
    SetShort("一个烂苹果");
    SetLong("这是一个发臭的、变 browned 的、看起来腐烂的苹果。");
    SetMass(5);
    SetStrength(-5);
    SetDollarCost(1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃了你的烂苹果。恶心！",
            "$N 吃了 $P 的烂苹果。恶心！");
}
void init(){
    ::init();
}
