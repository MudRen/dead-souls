#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("deer");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一头鹿");
    SetLong("这是一种典型的同类生物：紧张、鬼鬼祟祟，却又美丽而优雅。这种温顺的食草动物只想吃草和繁衍后代。");
    SetWimpy(95);
    SetPacifist(1);
    SetWanderSpeed(4);
    SetLevel(1);
    SetMelee(1);
    SetRace("deer");
    SetGender("female");
}
void init(){
    ::init();
}
