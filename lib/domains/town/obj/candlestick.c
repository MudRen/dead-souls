#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;
void create(){
    ::create();
    SetKeyName("silver candlestick");
    SetId( ({"candlestick","candelabra","candelabrum"}) );
    SetAdjectives( ({"small","ornate","silver"}) );
    SetShort("一个银烛台");
    SetLong("这是一个小巧精致的银烛台。");
    SetMass(20);
    SetBaseCost("silver",50);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
