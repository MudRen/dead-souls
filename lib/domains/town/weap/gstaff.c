#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
protected void create(){
    item::create();
    SetKeyName("golden staff");
    SetId( ({ "staff"  }) );
    SetAdjectives( ({ "golden" }) );
    SetShort("一根金色法杖");
    SetLong("这是一根粗法杖，一端覆盖着金色的金属。它看起来很强大。");
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetBaseCost("silver",800);
    SetMass(100);
    SetWeaponType("blunt");
    SetDamageType(BLUNT);
}
