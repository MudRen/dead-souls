#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("pull-pin");
    SetId(({"pin","ring"}));
    SetAdjectives(({"pull","grenade","fuse"}));
    SetShort("手榴弹拉环");
    SetLong("这是手榴弹引信上的拉环。");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
