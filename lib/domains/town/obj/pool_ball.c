#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("billiards ball");
    SetId( ({"ball"}) );
    SetAdjectives( ({"pool","billiards","billiard","heavy"}) );
    SetShort("一个台球");
    SetLong("这是一个重球，比掌心稍小，表面光滑有光泽。");
    SetMass(30);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
