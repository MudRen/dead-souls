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
    SetMealMessages("You eat a ham sandwich. Mmm!",
            "$N eats $P ham sandwich.");
}
void init(){
    ::init();
}
