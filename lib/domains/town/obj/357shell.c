#include <lib.h>
#include <vendor_types.h>
inherit LIB_SHELL;

void create(){
    ::create();
    SetKeyName("357shell");
    SetId(({"shell","casing","spent bullet"}));
    SetAdjectives(({".357",".357","spent","magnum","shell"}));
    SetShort("一个.357弹壳");
    SetLong("这是一枚.357马格南子弹的用过的弹壳。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetAmmoType("magnum");
    SetVendorType(VT_TREASURE);
    SetMass(1);
}

void init(){
    ::init();
}
