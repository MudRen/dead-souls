#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("drink");
    SetId(({"drink","generic drink"}));
    SetShort("普通饮料");
    SetLong("这是一杯普通饮料。");
    SetMass(10);
    SetStrength(20);
    SetBaseCost("silver",10);
    SetMealType(MEAL_DRINK);
    SetMealMessages("你一饮而尽。嗯！",
            "$N一饮而尽了$P的饮料。");
    SetNoCondition(1);
}
void init(){
    ::init();
}
