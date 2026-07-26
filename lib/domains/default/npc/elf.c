#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("elf");
    SetAdjectives( ({"arrogant", "smug", "malicious"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个傲慢的精灵");
    SetLong("哦，别被愚弄了。精灵们喜欢假装他们相信平等什么的，但他们都在暗自窃喜自己比人类聪明、长寿、智慧得多。你难道不想揍这个精灵那自鸣得意的小傻笑吗？");
    SetLevel(1);
    SetMelee(1);
    SetRace("elf");
    SetGender("male");
}
void init(){
    ::init();
}
