#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("bread");
    SetAdjectives( ({ "black","orc","orcish"}) );
    SetShort("一条黑面包");
    SetLong("一条用简单廉价方式烘焙的面包。");
    SetNoCondition(1);
    SetMass(50);
    SetStrength(10);
    SetBaseCost("silver", 1);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃了你的黑面包。",
            "$N 吃了 $P 的黑面包。");
}

void init(){
    ::init();
}
