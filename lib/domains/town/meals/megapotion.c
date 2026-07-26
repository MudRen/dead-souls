#include <lib.h>
#include <meal_types.h>

inherit LIB_POTION;

protected void create() {
    potion::create();
    SetKeyName("potion");
    SetId( ({ "potion","philtrum","megapotion","megapotion of uberness" }) );
    SetShort("一瓶超级强力药水");
    SetLong("一种力量完全超出比例的药水。");
    SetMass(60);
    SetMealType(MEAL_DRINK | MEAL_ALCOHOL);
    SetStrength(5);
    SetMealMessages("你喝了一瓶药水。",
            "$N 喝了一瓶药水。");
    SetBaseCost("silver",10000);
    SetDuration(30);
    SetStats( ([ "strength" : 50, "speed" : 50 ]) );
    SetSkills( ([ "bargaining" : 20, "melee defense" : 20 ]) );
    SetPoints( ([ "HP" : 100, "XP" : 100, "SP" : 100, "MP" : 100 ]) );
}
void init(){
    ::init();
}
