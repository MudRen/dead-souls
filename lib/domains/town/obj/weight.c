#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("weight");
    SetAdjectives( ({"iron", "heavy"}) );
    SetId( ({"iron", "item", "thing"}) );
    SetShort("一个铁砝码");
    SetLong("这是一个铁制物品，唯一的用途就是重。");
    SetMass(1800);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
