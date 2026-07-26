#include <lib.h>
#include <meal_types.h>
inherit LIB_MEAL;

protected void create() {
    meal::create();
    SetKeyName("dish");
    SetId(({"salad","dish of salad","dish"}));
    SetShort("一碟沙拉");
    SetLong("这碟昂贵的小菜由一些枯萎的生菜和两片橙色的番茄片组成。不过，它对心脏的危害可比小吃店的汉堡小多了。");
    SetMass(5);
    SetMealType(MEAL_FOOD);
    SetStrength(2);
    //SetDollarCost(3);
    SetDollarCost(3);
    SetMealMessages("You finish your salad before you realize it.","$N eats "+
            "$P salad in two bites.");
    SetEmptyName("dish");
    SetEmptyShort("an empty little plastic salad dish");
    SetEmptyLong("This little dish used to contain a salad.");
}
void init(){
    ::init();
}
