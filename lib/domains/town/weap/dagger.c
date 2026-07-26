#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("sharp dagger");
    SetId( ({ "dagger"}));
    SetAdjectives( ({ "sharp","fine","wicked","wicked-looking"}));
    SetShort("一把邪恶的匕首");
    SetLong("一把锋利的邪恶匕首。");
    SetMass(150);
    SetBaseCost("silver",50);
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}
void init(){
    ::init();
}
