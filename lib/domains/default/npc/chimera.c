#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("chimera");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只可怕的 chimera");
    SetLong("这个可怕的生物是 lion 的头和身体、dragon 的头、goat 的另一个头、以及 serpent 作为尾巴的 unholy mix。它的头 bob ceaselessly，眼睛 rolling madly in their sockets，嘴巴 opening and snapping shut。");
    SetClass("fighter");
    SetLevel(15);
    SetMelee(1);
    SetRace("chimera");
    SetGender("male");
}
void init(){
    ::init();
}
