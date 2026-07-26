#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("balrog");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort="一只 fierce 炎魔");
    SetLong("这是你 worst Nightmare 中的 terrifying demon！");
    SetWanderSpeed(5);
    SetClass("fighter");
    SetMelee(1);
    SetLevel(50);
    SetRace("balrog");
    SetGender("male");
}
void init(){
    ::init();
}
