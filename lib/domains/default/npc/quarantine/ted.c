#include <lib.h>

inherit LIB_SENTIENT;


protected void create() {
    sentient::create();
    SetKeyName("Ted");
    SetId(({"ted"}));
    SetShort("泰德");
    SetLong("泰德是虚拟校园的一名学生。");
    SetLevel(5);
    SetRace("human");
    SetGender("male");
    SetNoClean(1);
}
void init(){
    ::init();
}
