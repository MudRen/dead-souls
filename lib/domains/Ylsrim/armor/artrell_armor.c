/*    /domains/Ylsrim/armor/artrell_armor.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960302
 */

#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;

protected void create() {
    armor::create();
    SetKeyName("leather armor");
    SetId( ({ "armor", "leather armor" }) );
    SetAdjectives( ({ "leather" }) );
    SetShort("一套皮甲");
    SetLong("一套普通的皮甲。穿戴在手臂、躯干和腿部。");
    SetVendorType(VT_ARMOR);
    SetMass(750);
    SetValue(150);
    SetDamagePoints(800);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 25);
    SetProtection(HEAT, 7);
    SetProtection(COLD, 4);
    SetProtection(SHOCK, 15);
    SetArmorType(A_ARMOR);
}
void init(){
    ::init();
}
