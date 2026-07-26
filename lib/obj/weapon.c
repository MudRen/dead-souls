#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;


protected void create() {
    item::create();
    SetKeyName("generic weapon");
    SetId( ({ "weapon"}));
    SetAdjectives( ({ "generic" }));
    SetShort("普通武器");
    SetLong("一件尺寸不定的武器。");
    SetMass(50);
    SetVendorType(VT_WEAPON);
    SetClass(30);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
void init(){
    ::init();
}
