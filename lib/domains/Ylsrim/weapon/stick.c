/*    /domains/Ylsrim/weapon/stick.c
 *    From the Dead Souls Mud Library
 *    An example simple weapon
 *    Created by Descartes of Borg 970101
 */

#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("stick");
    SetId("stick");
    SetAdjectives("wooden");
    SetShort("一根木棍");
    SetLong("一根木棍，看起来可能曾经被用作拐杖，或者是穷人的棍棒。");
    SetMass(30);
    SetValue(10);
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetDamageType(BLUNT);
    SetWeaponType("blunt");
}
