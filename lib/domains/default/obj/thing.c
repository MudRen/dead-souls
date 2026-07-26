#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
void create(){
    ::create();
    SetKeyName("generic thing");
    SetId( ({"thing","item","thang","dingus"}) );
    SetAdjectives( ({"generic","sample","template"}) );
    SetShort("一个通用物品");
    SetLong("这是一个 indeterminate nature and proportions 的物品。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
