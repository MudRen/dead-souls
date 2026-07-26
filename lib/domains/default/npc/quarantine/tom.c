#include <lib.h>

inherit LIB_SENTIENT;


protected void create() {
    sentient::create();
    SetKeyName("Tom");
    SetId(({"tom"}));
    SetShort("汤姆");
    SetLong("汤姆是虚拟校园的一名学生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
