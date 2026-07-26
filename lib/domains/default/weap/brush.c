#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
protected void create(){
    item::create();
    SetKeyName("brush");
    SetId( ({ "brush"  }) );
    SetAdjectives( ({ "bath","shower","wood","wooden" }) );
    SetShort("一个淋浴刷");
    SetLong("这是一个长柄木刷，末端有 soft bristles， designed to assist in reaching tough-to-scrub areas while bathing。");
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetMass(100);
    SetWeaponType("blunt");
    SetDamageType(BLUNT);
}
