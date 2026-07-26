#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create(){
    item::create();
    SetKeyName("crowbar");
    SetId( ({ "rod" }) );
    SetAdjectives( ({ "heavy", "iron"}) );
    SetShort("撬棍");
    SetLong("这是一根沉重的铁棍，两端专门设计用来撬开东西。");
    SetVendorType(VT_WEAPON);
    SetClass(20);
    SetBaseCost("silver",150);
    SetMass(100);
    SetWeaponType("blunt");
    SetHands(1);
    SetDamageType(BLUNT);
}

void init(){
    ::init();
}
