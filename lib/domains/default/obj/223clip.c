#include <lib.h>
#include <vendor_types.h>
inherit LIB_CLIP;

void create(){
    clip::create();
    SetKeyName(".223 clip");
    SetId(({"clip","magazine"}));
    SetAdjectives(({".223","rifle","caliber","ammo","ammunition"}));
    SetShort("一个.223口径步枪弹匣");
    SetLong("这是一个用于.223口径步枪的弹簧式弹匣，"+
            "最多可容纳三十发子弹。");
    SetCaliber(223);
    SetMaxAmmo(30);
    SetAmmoType("nato");
    SetVendorType(VT_TREASURE);
    SetInventory(([
                "/domains/default/obj/223round" : 30,
                ]));
}
void init(){
    ::init();
}
