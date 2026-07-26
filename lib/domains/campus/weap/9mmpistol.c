#include <lib.h>
#include <vendor_types.h>
inherit "/lib/pistol";
void create(){
    pistol::create();
    SetKeyName("gun");
    SetId(({"gun","pistol"}));
    SetAdjectives(({"9mm","automatic","9 millimeter","semiautomatic"}));
    SetShort("9毫米半自动手枪");
    SetLong("This is a large, semiautomatic pistol that fires 9mm rounds. It is "+
            "a heavy, serious-looking weapon.");
    SetMillimeter(9);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetMass(30);
    SetDollarCost(3000);
    SetVendorType(VT_WEAPON);
}
