#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;

protected void create() {
    armor::create();
    SetKeyName("large shield");
    SetId( ({ "shield" }) );
    SetAdjectives( ({ "wood", "wooden","large" }) );
    SetShort("一面大木盾");
    SetLong("一面由铁箍加固的结实木材制成的大而重的盾牌。");
    SetVendorType(VT_ARMOR);
    SetMass(100);
    SetBaseCost("silver",250);
    SetArmorType(A_SHIELD);
    SetProtection(BLUNT, 10);
    SetProtection(BLADE, 10);
    SetProtection(KNIFE, 10);
    //SetRestrictLimbs( ({"left hand"}) );
}

void init(){
    ::init();
}
