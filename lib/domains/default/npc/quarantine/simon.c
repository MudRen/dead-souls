#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("Simon");
    SetId(({"simon"}));
    SetShort("西蒙");
    SetLong("西蒙是一名来自英国的交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
