#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dwarf");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个矮人");
    SetLong("这是你典型的看起来 hearty、矮小、强壮的矮人。红润的脸颊， full beard， the works。这个 straight out of central casting。");
    SetLevel(1);
    SetMelee(1);
    SetRace("dwarf");
    SetGender("male");
}
void init(){
    ::init();
}
