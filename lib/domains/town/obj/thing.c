#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("generic thing");
    SetId( ({"thing","item","thang","dingus"}) );
    SetAdjectives( ({"generic","sample","template"}) );
    SetShort("一个普通物品");
    SetLong("这是一个性质和大小都不确定的物品。");
    SetMass(1);
    SetBaseCost("silver",1);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
