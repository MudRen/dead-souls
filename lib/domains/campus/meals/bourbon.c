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
    SetId( ({ "bottle", "bourbon" }) );
    SetShort("一瓶波旁威士忌");
    SetLong("一瓶廉价波旁威士忌，装在深绿色的瓶子里。");
    SetMass(100);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(100);
    SetMealMessages("你喝完了波本威士忌，倒吸一口气！好烈的酒！",
            "$N 喝完一瓶波本威士忌，发出一声叛逆的呐喊！");
    SetEmptyName("bottle");
    SetEmptyShort("一个空的波本威士忌瓶");
    SetEmptyLong("这是一个空的绿色瓶子，曾经装着波本威士忌。");
}
void init(){
    ::init();
}
