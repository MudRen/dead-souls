#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("Wim");
    SetId(({"wim"}));
    SetShort("维姆");
    SetLong("维姆是来自荷兰的外国交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
}
void init(){
    ::init();
}
