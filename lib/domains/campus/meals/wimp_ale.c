/*    /domains/Praxis/etc/ale.c
 *    from Dead Souls
 *    created by Descartes of Borg 950603
 */

#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("ale");
    SetId( ({ "bottle", "ale", "praxis ale" }) );
    SetShort("一瓶麦酒");
    SetLong("一瓶好喝的拉尔斯著名普拉克西斯麦酒。");
    SetMass(60);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(1);
    SetMealMessages("You drink a wonderful bottle of Praxis Ale.",
            "$N drinks a wonderful bottle of Praxis Ale.");
    SetEmptyName("bottle");
    SetEmptyShort("an empty bottle of Praxis Ale");
    SetEmptyLong("It is an empty brown bottle that once held some ale.");
}
