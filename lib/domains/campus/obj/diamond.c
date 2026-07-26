#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("diamond");
    SetAdjectives( ({"fabled", "beautiful", "princess", "princess daphne"}) );
    SetId( ({"gem", "gemstone"}) );
    SetShort("美丽的钻石");
    SetLong("这就是传说中的达芙妮公主钻石。它是一颗美丽的宝石。");
    SetMass(200);
    SetBaseCost("dollars", 50000);
    SetVendorType(VT_TREASURE);
    SetProperty("gem", 1);
}
void init(){
    ::init();
}
