#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("minotaur");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("牛头人");
    SetLong("这是可怕的怪物，无数处女被献祭给它。它令人毛骨悚然，八英尺高，身体似乎由铁一般的肌肉组成，头是狂暴的公牛。它是如此可怕，以至于激发了一种催眠般的敬畏，很容易把它视为值得崇拜的自然力量。");
    SetClass("fighter");
    SetLevel(30);
    SetMelee(1);
    SetRace("demi-god");
    SetGender("male");
}
void init(){
    ::init();
}
