#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("centaur");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个半人马");
    SetLong("总是令人惊叹的景象，这是一种下半身是雄鹿，但头部位置是人的躯干，有手臂和头的生物。这个鹿/人看起来相当狂野，看起来完全像传说中那样不可预测。");
    SetWanderSpeed(10);
    SetLevel(1);
    SetMelee(1);
    SetRace("centaur");
    SetGender("male");
}
void init(){
    ::init();
}
