#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("bourbon");
    SetAdjectives( ({ "dark","green","cheap","bourbon" }) );
    SetId( ({ "bottle", "bottle of bourbon" }) );
    SetShort("一瓶波本威士忌");
    SetLong("一瓶深绿色的廉价波本威士忌。");
    SetMass(100);
    SetBaseCost("silver",20);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(30);
    SetMealMessages("You finish off the bourbon and gasp! WHEW!! Mean stuff!",
            "$N finishes off a bottle of bourbon and gasps.");
}
void init(){
    ::init();
}
