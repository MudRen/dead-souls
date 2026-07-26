#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("lab key");
    SetAdjectives( ({"engineering", "lab", "probability lab"}) );
    SetId( ({"prob_door_key", "key", "labkey"}) );
    SetShort("钥匙");
    SetLong("这是一把标有'工程和实验室'的钥匙。");
    SetMass(20);
    SetBaseCost("silver",10);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
