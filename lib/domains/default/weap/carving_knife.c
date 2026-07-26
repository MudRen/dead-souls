#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;


protected void create() {
    item::create();
    SetKeyName("carving knife");
    SetId( ({ "knife"}));
    SetAdjectives( ({ "serrated","sharp","razor sharp","steel","hefty","stainless","carving"}));
    SetShort("一把锯齿 carving knife");
    SetLong("这是一把锯齿 carving knife。这把 razor sharp knife has been forged from molded and hammered high-carbon stainless steel。它是 solid, hefty, and well-balanced。这是一把危险的刀，可以 considered a very deadly weapon。");
    SetMass(50);
    SetVendorType(VT_WEAPON);
    SetClass(30);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}
void init(){
    ::init();
}
