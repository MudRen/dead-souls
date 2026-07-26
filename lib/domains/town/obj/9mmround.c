#include <lib.h>
#include <vendor_types.h>
inherit "/lib/round";

void create(){
    ::create();
    SetKeyName("9mmround");
    SetId(({"round","bullet"}));
    SetAdjectives(({"9 millimeter","9mm","pistol"}));
    SetShort("一颗9毫米手枪子弹");
    SetLong("这是一颗9毫米手枪子弹，尚未击发。");
    SetMillimeter(9);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetVendorType(VT_TREASURE);
    SetMass(1);
}
