#include <lib.h>
#include <vendor_types.h>
inherit LIB_ROUND;

void create(){
    round::create();
    SetKeyName("223round");
    SetId(({"round","bullet"}));
    SetAdjectives(({".223","caliber","rifle","m16","M16","m-16","M-16"}));
    SetShort("一颗.223口径步枪子弹");
    SetLong("这是一颗.223口径步枪子弹，可能用于M-16突击步枪。它不太宽，但装有大量火药。无疑是一种强力弹药。尚未击发。");
    SetCaliber(223);
    SetMass(1);
    SetFirearmType("auto");
    SetFirearmType("auto");
    SetAmmoType("nato");
    SetVendorType(VT_TREASURE);
}
