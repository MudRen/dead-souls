#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dragon");
    SetAdjectives( ({"huge", "red", "dangerous"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一条红龙");
    SetLong("传说和寓言中的古老反派，红龙是周围最凶猛、残忍、危险的野兽之一。这条龙足有十五英尺高，可能毫不费力就能把你压扁。");
    SetClass("fighter");
    SetLevel(15);
    SetMelee(1);
    SetRace("dragon");
    SetGender("male");
}
void init(){
    ::init();
}
