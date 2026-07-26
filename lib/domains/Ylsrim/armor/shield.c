/*    /domains/Ylsrim/armor/shield.c
 *    from the Dead Souls Mud Library
 *    an example shield
 *    created by Lassondra@Dead Souls
 */

#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;

varargs int eventWearShield(object who, mixed where);

protected void create() {
    armor::create();
    SetKeyName("wooden shield");
    SetId( ({ "shield", "wooden shield" }) );
    SetShort("一面木盾");
    SetLong("这面盾牌是一个没有标记的简单圆形木盾。");
    SetDamagePoints(600);
    SetVendorType(VT_ARMOR);
    SetMass(400);
    SetValue(75);
    SetArmorType(A_SHIELD);
    SetWear( (: eventWearShield :) );
    SetProtection(BLUNT, 5);
    SetProtection(BLADE, 3);
    SetProtection(KNIFE, 10);
    SetProtection(SHOCK, 30);
}

varargs int eventWearShield(object who, mixed where) {
    object env = environment(who);
    if( who->GetRace() != "hobbit" ) {
        who->eventPrint("盾牌的把手就是不适合你的手。");
        return 0;
    }
    who->eventPrint("You wear "+GetShort()+".");
    if(env) tell_room(env, who->GetName()+" wears "+GetShort()+".", ({who}));
    return 1;
}
