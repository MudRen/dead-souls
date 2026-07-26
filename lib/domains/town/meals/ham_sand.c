#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("sandwich");
    SetId(({"sandwich","ham sandwich"}));
    SetShort("一个火腿三明治");
    SetLong("这是一个很大的普通火腿三明治。");
    SetMass(10);
    SetStrength(20);
    SetBaseCost("silver",10);
    SetMealType(MEAL_FOOD);
    SetMealMessages("你吃了一个火腿三明治。嗯！",
            "$N 吃了 $P 的火腿三明治。");
}
void init(){
    ::init();
}
