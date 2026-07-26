#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("deer");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一头鹿");
    SetLong("一个典型的同类生物：紧张、狡猾，但又美丽优雅。这只温顺的食草动物只想吃植物和繁殖。");
    SetWanderSpeed(4);
    SetLevel(1);
    SetMelee(1);
    SetRace("deer");
    SetGender("female");
}
void init(){
    ::init();
}
