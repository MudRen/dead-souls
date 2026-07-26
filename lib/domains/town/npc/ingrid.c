#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("ingrid");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("英格丽德");
    SetLong("英格丽德身材相当纤细，但她那不苟言笑的气质让她看起来比外表坚强得多。");
    SetInventory(([
                "/domains/town/armor/hshirt" : "wear shirt",
                "/domains/town/armor/workboot_l" : "wear left boot",
                "/domains/town/armor/bandanna" : "wear bandanna",
                "/domains/town/armor/workboot_r" : "wear right boot",
                "/domains/town/armor/workglove_r" : "wear right glove",
                "/domains/town/armor/jeans" : "wear jeans",
                "/domains/town/armor/workglove_l" : "wear left glove",
                "/domains/town/armor/lvest" : "wear vest",
                ]));
    SetLevel(1);
    SetMelee(1);
    SetRace("human");
    SetGender("female");
}
void init(){
    ::init();
}
