#include <lib.h>
#include <vendor_types.h>
inherit LIB_CLIP;

void create(){
    clip::create();
    SetKeyName(".223 clip");
    SetId(({"clip","magazine"}));
    SetAdjectives(({".223","rifle","caliber","ammo","ammunition"}));
    SetShort("一个.223口径步枪弹夹");
    SetLong("这是一个弹簧式弹夹，适用于.223口径步枪。最多可容纳三十发子弹。");
    SetCaliber(223);
    SetMaxAmmo(30);
    SetMass(5);
    SetAmmoType("nato");
    SetVendorType(VT_TREASURE);
    SetInventory(([
                "/domains/town/obj/223round" : 30,
                ]));
    SetBaseCost("silver", 75);
}
void init(){
    ::init();
}
