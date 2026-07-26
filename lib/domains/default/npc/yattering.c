#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("yattering");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个邪恶的小恶魔");
    SetLong("这是一个可怜的、肉粉色的生物，大约两英尺高。它有长长的、下垂的耳朵，一个鸟喙状的嘴巴，背上有一对无用的翅膀残肢。它的整体举止是无精打采的，不知为何还带着怨恨。尽管它看起来很可怜，但它拥有长长的黑色爪子，它的鸟喙看起来足够锋利。");
    SetClass("fighter");
    SetLevel(5);
    SetMelee(1);
    SetRace("demon");
    SetGender("male");
}
void init(){
    ::init();
}
