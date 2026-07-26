/*    /domains/Examples/armor/glove.c
 *    from the Dead Souls LPC Library
 *    an example glove
 *    created by Descartes of Borg 950408
 */

#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;

protected void create() {
    armor::create();
    SetKeyName("white glove");
    SetId( ({ "glove" }) );
    SetAdjectives( ({ "left", "white" ,"simple","elegant"}) );
    SetShort("白手套");
    SetLong("一只简洁而优雅的白色五指左手手套。");
    SetDamagePoints(75);
    SetVendorType(VT_ARMOR);
    SetMass(10);
    SetDollarCost(10);
    SetArmorType(A_GLOVE);
    SetRestrictLimbs( ({"left hand"}) );
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 1);
    SetProtection(KNIFE, 2);
    SetProtection(HEAT, 3);
    SetProtection(COLD, 7);
    SetFingers(5);
}
void init(){
    ::init();
}
