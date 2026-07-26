#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("chimera");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只可怕的喀迈拉");
    SetLong("这个可怕的生物是狮子的头和身体、龙的头、山羊的另一个头、以及蛇作为尾巴的邪恶混合体。它的头不停地晃动，眼睛在眼眶中疯狂转动，嘴巴一张一合。");
    SetClass("fighter");
    SetLevel(15);
    SetMelee(1);
    SetRace("chimera");
    SetGender("male");
}
void init(){
    ::init();
}
