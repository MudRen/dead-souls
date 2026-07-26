#include <lib.h>
#include <vendor_types.h>
inherit LIB_ROUND;


void create(){
    round::create();
    SetKeyName("223round");
    SetId(({"round","bullet"}));
    SetAdjectives(({".223","caliber","rifle","m16","M16","m-16","M-16"}));
    SetShort("一发.223口径步枪弹");
    SetLong("这是一发.223口径步枪弹，可能是用于M-16突击步枪的。"+
            "它不是很宽，但含有大量火药装药。毫无疑问这是一发强力弹药。它还没有被击发。");
    SetCaliber(223);
    SetFirearmType("auto");
    SetAmmoType("nato");
    SetVendorType(VT_TREASURE);
}
void init(){
    ::init();
}
