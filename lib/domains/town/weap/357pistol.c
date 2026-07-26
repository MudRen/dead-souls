#include <lib.h>
#include <vendor_types.h>
inherit LIB_FIREARM;

void create(){
    ::create();
    SetKeyName("gun");
    SetId(({"gun","pistol","piece","revolver"}));
    SetAdjectives(({".357","357","magnum"}));
    SetShort("一把.357马格南左轮手枪");
    SetLong("这是一块厚重的武器，发射非常强大的.357马格南子弹。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetFirearmName("revolver");
    SetAmmoType("magnum");
    SetMaxAmmo(6);
    SetMass(20);
    SetValue(10);
    SetVendorType(VT_WEAPON);
    SetMagnum(30);
}
void init(){
    ::init();
}
