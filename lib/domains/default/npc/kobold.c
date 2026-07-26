#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("kobold");
    SetAdjectives( ({"lizard", "short", "humanoid"}) );
    SetId( ({"lizard", "lizard man", "creature"}) );
    SetShort("一个矮小的蜥蜴人");
    SetLong("这个三英尺高的蜥蜴生物是狗头人。它的特征像爬行动物，但有着人类一样的手臂和腿。");
    SetLevel(1);
    SetMelee(1);
    SetRace("kobold");
    SetGender("male");
}
void init(){
    ::init();
}
