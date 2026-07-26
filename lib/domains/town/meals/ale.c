#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("ale");
    SetId( ({ "bottle", "ale", "first class ale", "first-class ale" }) );
    SetShort("一瓶麦芽酒");
    SetLong("一瓶不错的麦芽酒。");
    SetMass(60);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(5);
    SetMealMessages("你喝了一瓶麦芽酒。",
            "$N 喝了一瓶麦芽酒。");
    SetBaseCost("silver",10);
}
void init(){
    ::init();
}
