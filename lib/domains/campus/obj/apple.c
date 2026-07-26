#include <lib.h>
#include <vendor_types.h>
inherit LIB_ITEM;

void create(){
    ::create();
    SetKeyName("rotten apple");
    SetId( ({"apple","fruit"}) );
    SetAdjectives( ({"rotten","foul-smelling","dried-up","browned","brown"}) );
    SetShort("腐烂的苹果");
    SetLong("这是一个变褐色、恶臭、干瘪的苹果。");
    SetMass(5);
    SetDollarCost(0);
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
