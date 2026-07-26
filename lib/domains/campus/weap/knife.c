#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("knife");
    SetId( ({ "knife"}));
    SetAdjectives( ({ "small","utility"}));
    SetSmall("小多功能刀");
    SetLong("一把小多功能刀。");
    SetMass(40);
    SetBaseCost("silver",5);
    SetVendorType(VT_WEAPON);
    SetClass(2);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}

void init(){
    ::init();
}
