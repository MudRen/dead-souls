#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create()  {
    meal::create();
    SetKeyName("water");
    SetId(({ "bottle","water"}));
    SetAdjectives(({"fresh","spring"}));
    SetShort("一瓶水");
    SetLong("这是一小瓶新鲜的矿泉水。");
    SetMass(10);
    SetMealType(MEAL_DRINK);
    SetStrength(10);
    SetBaseCost("silver",2);
    SetMealMessages("你喝了你的水，感到神清气爽。", "$N 喝了 $P 的水。");
}
void init(){
    ::init();
}
