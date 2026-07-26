#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("kwyjibo");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"bald","overweight","dumb","stupid","North American","American"}));
    SetShort("一只大猩猩");
    SetLong("一只秃顶、超重、智力低于平均水平的北美猿类。");
    SetWanderSpeed(20);
    SetClass("fighter");
    SetLevel(10);
    SetEncounter(100);
    SetMelee(1);
    SetRace("ape");
    SetGender("male");
}
void init(){
    ::init();
}
