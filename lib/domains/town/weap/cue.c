#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create(){
    item::create();
    SetKeyName("cue");
    SetId( ({ "stick", "pole" }) );
    SetAdjectives( ({ "wood","wooden", "pool", "billiards", "billiard"}) );
    SetShort("一根台球杆");
    SetLong("这是一根高度抛光的长木棍，用于打台球。");
    SetVendorType(VT_WEAPON);
    SetDamagePoints(50);
    SetClass(10);
    SetBaseCost("silver",150);
    SetMass(80);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
void init(){
    ::init();
}
