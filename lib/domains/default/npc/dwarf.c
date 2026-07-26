#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dwarf");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个矮人");
    SetLong("这是你典型的看起来健壮、矮小、强壮的矮人。红润的脸颊，满脸胡须，一应俱全。这简直就是从中央选角那里直接走出来的。");
    SetLevel(1);
    SetMelee(1);
    SetRace("dwarf");
    SetGender("male");
}
void init(){
    ::init();
}
