#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("hand grenade spoon");
    SetId(({"lever","spoon"}));
    SetAdjectives(({"grenade","hand grenade","metal","small"}));
    SetShort("小金属杠杆");
    SetLong("这是手榴弹的引信杠杆，也叫勺子。");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
