#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("claire");
    SetId( ({"nymph", "danes", "claire danes", "woman"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("克莱尔·丹尼斯");
    SetLong("这个纤细的自然精灵看起来相当迷茫，可能应该陪伴一位次级女神穿过林间空地。");
    SetLevel(1);
    SetMelee(1);
    SetRace("nymph");
    SetGender("female");
}
void init(){
    ::init();
}
