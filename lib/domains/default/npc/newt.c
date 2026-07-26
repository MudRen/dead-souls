#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("newt");
    SetAdjectives( ({"slimy"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一只蝾螈");
    SetLong("一种黏糊糊的两栖动物。");
    SetWimpy(80);
    SetWanderSpeed(3);
    SetMelee(1);
    SetLevel(1);
    SetRace("amphibian");
    SetClass("explorer");
    SetMaxHealthPoints(10);
    SetGender("male");
}
void init(){
    ::init();
}
