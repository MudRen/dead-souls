#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("pull-pin");
    SetId(({"pin","ring"}));
    SetAdjectives(({"pull","grenade","fuse"}));
    SetShort("一个手榴弹 pin");
    SetLong("这是手榴弹 fuse 的 pull pin。");
    SetMass(1);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
