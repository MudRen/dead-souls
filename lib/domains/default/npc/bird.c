#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dodo");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只胖嘟嘟的渡渡鸟");
    SetLong("这个愚蠢的小生物唯一的罪过就是生来就信任他人且味道鲜美。");
    SetWanderSpeed(10);
    SetLevel(1);
    SetMelee(1);
    SetRace("bird");
    SetMaxHealthPoints(30);
    SetGender("male");
}
void init(){
    ::init();
}
