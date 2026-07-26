#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("gargoyle");
    SetAdjectives( ({"stone", "grotesque", "ugly", "repellent"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个 grotesque 石像鬼");
    SetLong("一个石头精灵活了过来，这个 monstrosity was designed to be as ugly and repellent as anything could be and still hold its shape。它是 wildly successful。它的 rolling eyes and lolling tongue make it a horrid sight indeed。");
    SetLevel(1);
    SetMelee(1);
    SetRace("gargoyle");
    SetGender("male");
}
void init(){
    ::init();
}
