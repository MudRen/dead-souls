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
    SetLong("这根法杖又旧又破，但仍然很结实。它由某种坚硬的木材制成。");
    SetVendorType(VT_WEAPON);
    SetDamagePoints(50);
    SetClass(20);
    SetBaseCost("silver",250);
    SetMass(100);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
void init(){
    ::init();
}
