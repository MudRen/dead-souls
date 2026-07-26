#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("lynx");
    SetId(({"npc","mob","quadruped","mobile"}));
    SetAdjectives(({"non-player", "endothermic","carnivorous"}));
    SetShort("一只猞猁");
    SetLong("一种恒温四足动物，天生食肉，大约和中型狗一样大。它有巨大的耳朵，用来在黑暗中捕猎。");
    SetWanderSpeed(10);
    SetLevel(1);
    SetMelee(1);
    SetRace("cat");
    SetGender("male");
}
void init(){
    ::init();
}
