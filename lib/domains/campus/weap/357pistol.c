#include <lib.h>
#include <vendor_types.h>
inherit "/lib/pistol";

void create(){
    pistol::create();
    SetKeyName("revolver");
    SetId(({"gun","pistol","piece"}));
    SetAdjectives(({".357","357","magnum"}));
    SetShort(".357马格南左轮手枪");
    SetLong("这是一把厚重结实的武器，能发射非常厉害的子弹。子弹是一发一发装填的，子弹和用过的弹壳都会留在弹巢中，直到卸下。");
    SetCaliber(357);
    SetFirearmType("revolver");
    SetAmmoType("magnum");
    SetMaxAmmo(6);
    SetMass(20);
    SetDollarCost(10);
    SetVendorType(VT_WEAPON);
    SetMagnum(30);
}
void init(){
    ::init();
}
