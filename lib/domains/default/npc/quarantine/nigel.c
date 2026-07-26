#include <lib.h>

inherit LIB_SENTIENT;


protected void create() {
    sentient::create();
    SetKeyName("Nigel");
    SetId(({"nigel"}));
    SetShort("奈杰尔");
    SetLong("奈杰尔是一名来自英国的交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
