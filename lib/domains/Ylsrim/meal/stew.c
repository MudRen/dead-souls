/*    /domains/Ylsrim/meal/stew.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("elven stew");
    SetId( ({ "stew" }) );
    SetAdjectives( ({ "elven" }) );
    SetShort("一些热腾腾的精灵炖菜");
    SetLong("这道炖菜是用托拉尔餐厅其他菜肴的剩料制成的。");
    SetMass(10);
    SetMealType(MEAL_FOOD);
    SetStrength(3);
    SetMealMessages("炖菜让你的鼻腔通畅了！",
            "$N吃了精灵炖菜后精神焕发。");
}
