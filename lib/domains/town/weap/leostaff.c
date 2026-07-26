#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
protected void create(){
    item::create();
    SetKeyName("staff");
    SetId( ({ "staff", "stick", "pole"  }) );
    SetAdjectives( ({ "wood","wooden","strong","heavy","thick","sturdy","solid" }) );
    SetShort("一根大木杖");
    SetLong("这根法杖又粗又壮，由坚硬的木材制成。它看起来非常结实。");
    SetVendorType(VT_WEAPON);
    SetDamagePoints(50);
    SetClass(500);
    SetBaseCost("silver",25000);
    SetMass(700);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
