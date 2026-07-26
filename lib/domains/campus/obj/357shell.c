#include <lib.h>
#include <vendor_types.h>
inherit LIB_SHELL;

void create(){
    shell::create();
    SetKeyName("357shell");
    SetId(({"shell","casing","spent bullet"}));
    SetAdjectives(({".357","spent","magnum","shell"}));
    SetShort(".357口径弹壳");
    SetLong("这是.357马格南子弹的用过的弹壳。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetAmmoType("magnum");
    SetVendorType(VT_TREASURE);
}

void init(){
    shell::init();
}
