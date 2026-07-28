/*    /domains/Praxis/etc/ale.c
 *    from Dead Souls
 *    created by Descartes of Borg 950603
 */

#include <lib.h>
#include <meal_types.h>

inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("gatorade");
    SetId(({"gatorade","drink","sports drink","bottle"}));
    SetShort("一瓶佳得乐");
    SetLong("这是一瓶柠檬青柠味的佳得乐。");
    SetMass(60);
    SetBaseCost("silver", 2);
    SetMealType(MEAL_DRINK);
    SetStrength(40);
    SetMealMessages("你一口气喝完佳得乐，感觉焕然一新。啊！","$N 咕嘟咕嘟喝完$P佳得乐，满足地叹了口气。");
    SetEmptyName("bottle");
    SetEmptyShort("一个空的佳得乐瓶子");
    SetEmptyLong("这是一个空瓶子，曾经装着那种美味可口的运动饮料——佳得乐。");
}
void init(){
    ::init();
}
