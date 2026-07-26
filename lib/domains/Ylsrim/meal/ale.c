/*    /domains/Ylsrim/meal/ale.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("ale");
    SetId( ({ "bottle", "ale", "ylsrim ale" }) );
    SetShort("一瓶麦酒");
    SetLong("一瓶美味的拉尔斯著名伊尔斯利姆麦酒。");
    SetMass(60);
    SetBaseCost("electrum", 20);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(10);
    SetMealMessages("你喝了一瓶美味的伊尔斯利姆麦酒。",
            "$N喝了一瓶美味的伊尔斯利姆麦酒。");
    SetEmptyName("bottle");
    SetEmptyShort("一个空的伊尔斯利姆麦酒瓶");
    SetEmptyLong("这是一个曾经装过麦酒的空棕色瓶子。");
}
void init(){
    ::init();
}
