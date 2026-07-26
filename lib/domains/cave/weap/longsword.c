#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("longsword");
    SetId( ({ "sword","weapon" }) );
    SetAdjectives( ({ "long","well crafted","bladed","two handed" }) );
    SetShort("一把长剑");
    SetLong("一把精心打造的致命利刃，设计为双手握持。");
    SetMass(500);
    SetHands(2);
    SetBaseCost("silver",2800);
    SetVendorType(VT_WEAPON);
    SetClass(35);
    SetDamageType(BLADE);
    SetWeaponType("blade");
}

void init(){
    ::init();
}
