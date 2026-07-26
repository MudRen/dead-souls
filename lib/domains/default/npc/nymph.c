#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("claire");
    SetId( ({"nymph", "danes", "claire danes", "woman"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("克莱尔·丹尼斯");
    SetLong("这个 slender 的自然精灵看起来 quite lost， probably should be accompanying a lesser goddess through woodland glades。");
    SetLevel(1);
    SetMelee(1);
    SetRace("nymph");
    SetGender("female");
}
void init(){
    ::init();
}
