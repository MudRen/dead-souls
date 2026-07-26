#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("hand grenade spoon");
    SetId(({"lever","spoon"}));
    SetAdjectives(({"grenade","hand grenade","metal","small"}));
    SetShort="一个小金属 lever");
    SetLong("这是手榴弹的 fuse lever， or spoon。");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
