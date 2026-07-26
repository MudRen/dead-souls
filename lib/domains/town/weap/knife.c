#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("small knife");
    SetId( ({ "knife"}));
    SetAdjectives( ({ "small","fine"}));
    SetShort("一把小刀");
    SetLong("一把刀。");
    SetMass(50);
    SetBaseCost("silver",5);
    SetVendorType(VT_WEAPON);
    SetClass(5);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}

void init(){
    ::init();
}
