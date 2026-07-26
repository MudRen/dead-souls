#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("elephant");
    SetAdjectives( ({"docile", "pink", "friendly", "large", "very large"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一头粉色大象");
    SetLong("这是一个非常大的生物，但它看起来相当温顺，甚至很友好。不清楚粉色是天然的还是涂上去的，但相当好看。");
    SetLevel(1);
    SetMelee(1);
    SetRace("elephant");
    SetGender("female");
}
void init(){
    ::init();
}
