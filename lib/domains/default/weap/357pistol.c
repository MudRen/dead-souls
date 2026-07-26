#include <lib.h>
#include <vendor_types.h>
inherit LIB_FIREARM;

void create(){
    ::create();
    SetKeyName("gun");
    SetId(({"gun","pistol","piece","revolver"}));
    SetAdjectives(({".357","357","magnum"}));
    SetShort("一把.357麦格南左轮手枪");
    SetLong("这是一把厚重的武器，发射非常强力的弹药。"+
            "子弹逐一装入，连同用过的弹壳一起留在弹巢中，直到卸下。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetFirearmName("revolver");
    SetAmmoType("magnum");
    SetMaxAmmo(6);
    SetMass(20);
    SetBaseCost("silver", 1200);
    SetVendorType(VT_WEAPON);
    SetMagnum(30);
}
void init(){
    ::init();
}
