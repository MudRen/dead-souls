#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("bear");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一头熊");
    SetLong("一头大棕熊。虽然没有灰熊那么巨大，但也足够大到能把你打翻在地。");
    SetWanderSpeed(20);
    SetClass("fighter");
    SetLevel(10);
    SetMelee(1);
    SetRace("bear");
    SetGender("male");
}

void init(){
    ::init();
}
