/*    /domains/Examples/weapon/sword.c
 *    from the Dead Souls LPC Library
 *    a simple sword example, nothing fancy
 *    created by Descartes of Borg 950402
 */

#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("board of ed");
    SetId(({"board","board of ed","board of education"}));
    SetAdjectives(({"ed","education"}));
    SetShort("教育板");
    SetLong("一块又长又宽的木板，一端有把手。沿着板身刻着一行字：'教育委员会'。");
    SetMass(50);
    SetDollarCost(20);
    SetVendorType(VT_WEAPON);
    SetClass(20);
    SetDamageType(BLUNT);
    SetWeaponType("blunt");
}
