#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;


protected void create() {
    meal::create();
    SetKeyName("firebreather bourbon");
    SetId( ({ "bottle", "bourbon" ,"fire","firebreather",
                "bottle of bourbon"}) );
    SetAdjectives( ({ "firebreather","dark","green","bourbon"}) );
    SetShort("一瓶波本威士忌");
    SetLong("一瓶深绿色的\"火喉\"牌波本威士忌。");
    SetMass(100);
    SetBaseCost("silver",50);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(40);
    SetMealMessages("You finish off the bourbon and gasp! WHOOT!! Mean stuff!",
            "$N finishes off a bottle of Firebreather bourbon and lets loose a rebel yell!");
}

void init(){
    ::init();
}
