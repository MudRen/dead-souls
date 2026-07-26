#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("generic npc");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non player"}));
    SetShort("普通NPC");
    SetLong("除了是人类之外，这个NPC完全不起眼。");
    SetLevel(1);
    SetMelee(1);
    SetRace("human");
    SetGender("male");
}
void init(){
    ::init();
}
