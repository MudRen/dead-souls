#include <lib.h>
#include <meal_types.h>
#include <dirs.h>

inherit LIB_FISH;

protected void create() {
    fish::create();
    SetKeyName("zyqxuwy");
    SetId( ({ "fish", "pinkfish" }) );
    SetAdjectives( ({ "pink","freshwater","fresh water" }) );
    SetShort("一条粉色zyqxuwy鱼");
    SetLong("这是一种淡水鱼，粉色的。");
    SetMealType(MEAL_FOOD);
    SetMass(10); 
    SetStrength(10); 
    SetBaseCost("silver", 2);
    SetFight(4);
    SetFood("/domains/town/meals/zyqxuwy");
}
void init(){
    ::init();
}
