#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("artrell");
    SetAdjectives( ({"insectoid"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个 artrell");
    SetLong("如果不是因为它的昆虫般的外表和四条手臂，这种生物大致是人形的。它看起来比成年人类略显纤细矮小，但你仍然不会想碰它。这是你见过的最大的虫子。");
    SetLevel(1);
    SetRace("artrell");
    SetGender("male");
}
void init(){
    ::init();
}
