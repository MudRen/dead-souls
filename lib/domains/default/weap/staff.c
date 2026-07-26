#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
protected void create(){
    item::create();
    SetKeyName("staff");
    SetId( ({ "staff", "stick", "pole"  }) );
    SetAdjectives( ({ "wood","wooden" }) );
    SetShort("一根木杖");
    SetLong("这根法杖 old, weathered, and lumpy。然而，它 feels quite sturdy and solid。");
    SetVendorType(VT_WEAPON);
    SetDamagePoints(50);
    SetClass(100);
    SetMass(100);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
