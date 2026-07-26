#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("Fell Sword");
    SetId( ({"sword", "weapon", "fellsword"}) );
    SetAdjectives( ({"fell", "elvish", "powerful", "antique", "old"}) );
    SetShort("暗黑之剑");
    SetLong("一把具有悠久历史和巨大力量的精灵之剑。");
    SetUnique(1);
    SetMass(100);
    SetBaseCost("silver", 5000);
    SetVendorType(VT_WEAPON);
    SetClass(40);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
void init(){
    ::init();
}
