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
    SetShort("大型木盾");
    SetLong("一面大型重型盾牌，由坚固的木材制成，外加铁箍。");
    SetDamagePoints(75);
    SetVendorType(VT_ARMOR);
    SetMass(200);
    SetBaseCost("silver",150);
    SetArmorType(A_SHIELD);
    SetProtection(BLUNT, 10);
    SetProtection(BLADE, 10);
    SetProtection(KNIFE, 10);
    //SetRestrictLimbs( ({"left hand"}) );
}

