#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("artrell");
    SetAdjectives( ({"insectoid"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort="一个 artrell");
    SetLong("如果不是因为它的 insectoid appearance and four arms，这种生物 would be roughly humanoid。它 appears slightly thinner and smaller than an adult human， but you still don't want to touch it。 It's the biggest damned bug you've ever seen。");
    SetLevel(1);
    SetRace("artrell");
    SetGender("male");
}
void init(){
    ::init();
}
