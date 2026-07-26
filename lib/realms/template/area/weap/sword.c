#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("short sword");
    SetId( ({ "sword", "short sword" }) );
    SetAdjectives( ({ "short" }) );
    SetShort("一把短剑");
    SetLong("一把廉价且相当钝的短剑。");
    SetMass(300);
    SetBaseCost(50);
    SetVendorType(VT_WEAPON);
    SetClass(20);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
