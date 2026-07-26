#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
void create(){
    ::create();
    SetKeyName("generic thing");
    SetId( ({"thing","item","thang","dingus"}) );
    SetAdjectives( ({"generic","sample","template"}) );
    SetShort("普通物品");
    SetLong("这是一个性质和大小不确定的物品。");
    SetMass(20);
    SetDollarCost(10);
    SetVendorType(VT_TREASURE);
}
