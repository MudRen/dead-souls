#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gargoyle");
    SetAdjectives( ({"stone", "grotesque", "ugly", "repellent"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个怪诞的石像鬼");
    SetLong("一个石头精灵活了过来，这个怪物被设计得尽可能丑陋和令人厌恶，同时还能保持形状。它非常成功。它转动的眼睛和伸出的舌头确实让它看起来很恐怖。");
    SetLevel(1);
    SetMelee(1);
    SetRace("gargoyle");
    SetGender("male");
}
void init(){
    ::init();
}
