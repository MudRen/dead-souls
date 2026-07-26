#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("sharp sword");
    SetId( ({"sword"}) );
    SetAdjectives( ({ "short","sharp","fine"}));
    SetShort("一把锋利的剑");
    SetLong("一把精美锋利的剑。做工扎实，平衡性好。");
    SetMass(300);
    SetBaseCost("silver", 1100);
    SetVendorType(VT_WEAPON);
    SetClass(35);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
void init(){
    ::init();
}
