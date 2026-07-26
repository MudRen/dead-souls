#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("meal");
    SetId(({"meal","generic meal"}));
    SetShort("普通餐食");
    SetLong("这是一顿普通餐食。");
    SetMass(10);
    SetStrength(20);
    SetBaseCost("silver",10);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃完了食物。嗯！",
            "$N吃完了$P的食物。");
    SetNoCondition(1);
}
void init(){
    ::init();
}
