/*    /domains/Ylsrim/meal/shark.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("shark");
    SetId( ({ "blue shark", "shark", "fish" }) );
    SetAdjectives( ({ "blue" }) );
    SetShort("一条蓝鲨");
    SetLong("一条曾经看起来致命的蓝鲨，现在看起来很美味。");
    SetMass(100);
    SetMealType(MEAL_FOOD);
    SetStrength(25);
    SetMealMessages("味道好极了。", "$N吃了一条蓝鲨。");
}
