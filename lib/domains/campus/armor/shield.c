/*    /domains/Examples/armor/shield.c
 *    from the Dead Souls LPC Library
 *    an example shield
 *    created by Lassondra@Dead Souls
 */

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
    SetShort("大木盾");
    SetLong("一面由坚固木材制成的大而沉重的盾牌，用铁条加固。");
    SetDamagePoints(75);
    SetVendorType(VT_ARMOR);
    SetMass(100);
    SetDollarCost(150);
    SetArmorType(A_SHIELD);
    SetProtection(BLUNT, 10);
    SetProtection(BLADE, 10);
    SetProtection(KNIFE, 10);
    //SetRestrictLimbs( ({"left hand"}) );
}

