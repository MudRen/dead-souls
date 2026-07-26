#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("cow");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一头短角和牛");
    SetLong("以其精美的大理石纹路而闻名，和牛的肉被美食家们视为珍馐美味。这只温顺的动物习惯了被宠爱、喂养得很好，并且每天按摩三次。");
    SetWimpy(80);
    SetWanderSpeed(7);
    SetLevel(1);
    SetMelee(1);
    SetRace("cow");
    SetGender("female");
    SetAction(1, ({ "!emote rit." }) );
}
void init(){
    ::init();
}
