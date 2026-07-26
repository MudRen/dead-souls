#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("Wim");
    SetId(({"wim"}));
    SetShort("维姆");
    SetLong("维姆是一名来自荷兰的交换生。");
    SetMelee(1);
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
