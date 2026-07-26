#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("minotaur");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("牛头人");
    SetLong("这是可怕的怪物，无数处女被献祭给它。它 transcendentally horrifying，八英尺高，身体 seemingly of iron muscle，头是 raging bull。它是如此可怕，以至于激发了一种 hypnotic awe，很容易把它视为值得崇拜的自然力量。");
    SetClass("fighter");
    SetLevel(30);
    SetMelee(1);
    SetRace("demi-god");
    SetGender("male");
}
void init(){
    ::init();
}
