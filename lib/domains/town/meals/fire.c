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
    SetMealMessages("你喝完了波本威士忌，倒吸一口气！好烈的酒！",
            "$N 喝完一瓶\"火喉\"波本威士忌，发出一声叛逆的呐喊！");
}

void init(){
    ::init();
}
