#include <lib.h>

inherit LIB_SENTIENT;


protected void create() {
    sentient::create();
    SetKeyName("Trevor");
    SetId(({"trevor"}));
    SetShort("特雷弗");
    SetLong("特雷弗是一名来自英国的交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
