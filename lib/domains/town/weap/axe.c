#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("sharp axe");
    SetId( ({ "axe"}));
    SetAdjectives( ({ "sharp","small","hand"}));
    SetShort("一把短柄斧");
    SetLong("一把小巧锋利的手斧，适合近战。");
    SetMass(150);
    SetBaseCost("silver",50);
    SetVendorType(VT_WEAPON);
    SetClass(15);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
