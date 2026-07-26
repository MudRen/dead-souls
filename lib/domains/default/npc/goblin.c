#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("goblin");
    SetAdjectives( ({"malicious", "short", "green", "clever"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个矮小的绿色哥布林");
    SetLong("这个可怕的生物证实了你小时候听过的最糟糕的故事。它似乎从光滑的绿色皮肤中渗出恶意。它看起来很像巨魔，但更小更聪明，眼睛 almost appear to radiate poison and hatred。它的存在本身就污染了空气。");
    SetLevel(1);
    SetMelee(1);
    SetRace("goblin");
    SetGender("male");
}
void init(){
    ::init();
}
