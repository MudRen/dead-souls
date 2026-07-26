#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create()  {
    meal::create();
    SetKeyName("coffee");
    SetId( ({"cup","coffee" }) );
    SetAdjectives( ({"regular","cup of","ordinary"}) );
    SetShort("一杯咖啡");
    SetLong("一杯普通的咖啡"); 
    SetMass(10);
    SetMealType( MEAL_DRINK | MEAL_CAFFEINE );
    SetStrength(10);
    SetBaseCost("silver",5);
    SetMealMessages("The wonderful drink is invigorating." , 
            "$N drinks $P coffee, and looks invigorated.");
}
void init(){
    ::init();
}
