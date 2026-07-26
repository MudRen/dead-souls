#include <lib.h>

inherit LIB_STORAGE;

void create() {
    ::create();
    SetKeyName("locker");
    SetId(({"locker","object"}));
    SetAdjectives(({"metal","tall","large"}));
    SetShort("一个高大的金属储物柜");
    SetLong("这个大型物件 designed to hold armor and related accessories。");
    SetInventory(([
                "/domains/default/armor/pcannon" : 1,
                "/domains/default/armor/scoutsuit" : 1,
                "/domains/default/armor/chainmail" : 5,
                ]));
    SetMass(2000);
    SetBaseCost("silver",150);
    SetMaxCarry(10000);
    SetCanClose(1);
    SetClosed(0);
    SetPreventGet("这个储物柜纹丝不动。");
}
void init(){
    ::init();
}
