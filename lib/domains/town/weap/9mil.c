#include <lib.h>
#include <vendor_types.h>
inherit LIB_PISTOL;

void create(){
    ::create();
    SetKeyName("gun");
    SetId(({"gun","pistol"}));
    SetAdjectives(({"9mm","automatic","9 millimeter","semiautomatic"}));
    SetShort("一把9毫米半自动手枪");
    SetLong("这是一把大型半自动手枪，发射9毫米子弹。它很可靠，精度也不错。");
    SetMillimeter(9);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetMass(30);
    SetBaseCost("silver",900);
    SetVendorType(VT_WEAPON);
}
void init(){
    ::init();
}
