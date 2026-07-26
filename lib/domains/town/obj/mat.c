#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("bath mat");
    SetId( ({"mat"}) );
    SetAdjectives( ({"slightly damp","damp","blue","light blue"}) );
    SetShort("一张浴室垫");
    SetLong("这是一张浴室垫，用于防滑，促进安全。");
    SetMass(10);
    SetBaseCost("silver",5);
    SetVendorType(VT_TREASURE);
}

void init(){
    ::init();
}
