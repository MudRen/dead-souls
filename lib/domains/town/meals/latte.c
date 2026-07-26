#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create()  {
    meal::create();
    SetKeyName("milk");
    SetId("latte");
    SetShort("一杯拿铁咖啡");
    SetLong("一杯完美的浓缩咖啡与蒸汽牛奶的结合，上面还有一层奶泡。");
    SetMass(10);
    SetMealType( MEAL_DRINK | MEAL_CAFFEINE );
    SetStrength(25);
    SetValue(2);
    SetMealMessages("The wonderful drink is invigorating." , 
            "$N drinks $P latte, and looks invigorated.");
}
void init(){
    ::init();
}
