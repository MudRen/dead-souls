#include <lib.h>
#include <vendor_types.h>
inherit LIB_ROUND;

void create(){
    round::create();
    SetKeyName(".45 round");
    SetId(({"round","bullet"}));
    SetAdjectives(({".45","caliber","acp","pistol","semiautomatic"}));
    SetShort(".45口径手枪子弹");
    SetLong("这是一颗用于半自动手枪的.45口径子弹。它还没有被击发。");
    SetCaliber(45);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetVendorType(VT_TREASURE);
    SetMass(1);
}
