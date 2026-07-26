#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("sharp sword");
    SetId( ({"sword"}) );
    SetAdjectives( ({ "very", "short","sharp","fine"}));
    SetShort("一把非常锋利的剑");
    SetLong("一把非常好、锋利的剑。做工扎实，平衡性极佳。");
    SetMass(400);
    SetBaseCost("silver", 2500);
    SetVendorType(VT_WEAPON);
    SetClass(35);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}

void init(){
    ::init();
}
