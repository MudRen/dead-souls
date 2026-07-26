#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("Cor");
    SetId(({"cor"}));
    SetShort("科尔");
    SetLong("科尔是一名来自荷兰的交换生。");
    SetMelee(1);
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
