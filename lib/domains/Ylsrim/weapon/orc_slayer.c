/*    /domains/Ylsrim/weapon/orc_slayer.c
 *    From the Dead Souls Mud Library
 *    An example of a weapon that is nasty against orcs
 *    Created by Descartes of Borg 970101
 */

#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("orc slayer");
    SetId("sword", "slayer", "orcslayer");
    SetAdjectives("orc", "metal", "dull");
    SetShort("一把暗淡的长剑");
    SetLong("这把暗淡的长剑上刻着一些古老的符文。");
    SetRead("Orc Slayer");
    SetMass(140);
    SetValue(110);
    SetVendorType(VT_WEAPON);
    SetClass(18);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}

// eventStrike() gets called each time the weapon hits an enemy
int eventStrike(object target) {
    // call the default eventStrike() to get default damage
    int x = item::eventStrike(target);

    // check if the target is an orc
    if( target->GetRace() == "orc" ) {
        // send a cool message to everyone in the room
        // environment() is the person using the sword
        // environment(environment()) thus would be the room
        environment(environment())->eventPrint("斩兽剑因对兽人的仇恨而闪耀。");
        // add a random(5) to the default damage
        x += random(5);
    }
    // return the damage it should do
    return x;
}
