#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("halfling");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个半身人");
    SetLong("这种生物在外表上 almost identical to a hobbit，矮小的身材、毛茸茸的脚，显然还有爱玩的性格。通常需要 hobbit 或 halfling 才能区分他们，但 halfling 往往因为历史原因而被回避和忽视，所以如果它看起来有点穷和营养不良， like this one， it's a halfling。");
    SetLevel(1);
    SetMelee(1);
    SetRace("halfling");
    SetGender("male");
}
void init(){
    ::init();
}
