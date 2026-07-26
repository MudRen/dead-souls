#include <lib.h>
#include <vendor_types.h>
inherit LIB_ROUND;

void create(){
    round::create();
    SetKeyName(".357 round");
    SetId(({"round","bullet"}));
    SetAdjectives(({".357","caliber","revolver","pistol"}));
    SetShort("一颗.357手枪子弹");
    SetLong("这是一颗.357口径左轮手枪子弹，尚未击发。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetAmmoType("magnum");
    SetVendorType(VT_TREASURE);
    SetMass(1);
}
