#include <lib.h>
#include <vendor_types.h>
inherit LIB_PISTOL;

void create(){
    ::create();
    SetKeyName("gun");
    SetId(({"gun","pistol"}));
    SetAdjectives(({"9mm","automatic","9 millimeter","semiautomatic"}));
    SetShort("一把9毫米半自动手枪");
    SetLong("这是一把大型半自动手枪，发射9毫米弹药。"+
            "它是一件沉重、看起来很严肃的武器。");
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
