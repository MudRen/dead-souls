#include <lib.h>

inherit LIB_SENTIENT;


protected void create() {
    sentient::create();
    SetKeyName("lester");
    SetId(({"lester"}));
    SetShort("莱斯特");
    SetLong("莱斯特是一名来自英国的交换生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
