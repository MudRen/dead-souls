#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create(){
    item::create();
    SetKeyName("brush");
    SetId( ({ "brush"  }) );
    SetAdjectives( ({ "bath","shower","wood","wooden" }) );
    SetShort("一把沐浴刷");
    SetLong("这是一把长木刷，有柔软的刷毛，适合在沐浴时使用。");
    SetVendorType(VT_WEAPON);
    SetClass(10);
    SetBaseCost("silver",25);
    SetMass(100);
    SetWeaponType("blunt");
    SetDamageType(BLUNT);
}
void init(){
    ::init();
}
