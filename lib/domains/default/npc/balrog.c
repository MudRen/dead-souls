#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("balrog");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只凶猛的炎魔");
    SetLong("这是你最可怕噩梦中的恐怖恶魔！");
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
