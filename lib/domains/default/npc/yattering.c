#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("yattering");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个 foul 小恶魔");
    SetLong("这是一个 wretched, fleshy pink creature，大约两英尺高。它有长长的、下垂的耳朵，一个 beaklike mouth，背上有一对 useless wing stubs。它的 general demeanor is listless and somehow resentful。 As pathetic as it looks，它 possesses long black claws， and its beak looks plenty sharp。");
    SetClass("fighter");
    SetLevel(5);
    SetMelee(1);
    SetRace("demon");
    SetGender("male");
}
void init(){
    ::init();
}
