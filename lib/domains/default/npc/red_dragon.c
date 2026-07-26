#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("dragon");
    SetAdjectives( ({"huge", "red", "dangerous"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一条红龙");
    SetLong("传说和寓言中的 ancient villain，红龙是周围最 vicious、cruel、dangerous 的野兽之一。这条 easily fifteen feet tall， could probably crush you without even noticing。");
    SetClass("fighter");
    SetLevel(15);
    SetMelee(1);
    SetRace("dragon");
    SetGender("male");
}
void init(){
    ::init();
}
