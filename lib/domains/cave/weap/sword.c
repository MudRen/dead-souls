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
    SetBaseCost("silver",800);
    SetVendorType(VT_WEAPON);
    SetClass(15);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}
void init(){
    ::init();
}
