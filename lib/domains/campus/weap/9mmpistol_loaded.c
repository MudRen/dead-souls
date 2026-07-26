#include <lib.h>
#include <vendor_types.h>
inherit "/lib/pistol";

int AddClip();
void create(){
    pistol::create();
    SetKeyName("gun");
    SetId(({"gun","pistol"}));
    SetAdjectives(({"9mm","automatic","9 millimeter","semiautomatic"}));
    SetShort("9毫米半自动手枪");
    SetLong("这是一把大型半自动手枪，发射9毫米子弹。它是一把沉重的、看起来很厉害的武器。");
    SetMillimeter(9);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetMass(30);
    SetDollarCost(3000);
    SetVendorType(VT_WEAPON);
    AddClip();
    SetLoaded(1);
    SetAmmo(15);
    SetMag(1);
}
int AddClip(){
    if(!present("clip",this_object())){
        new("/domains/campus/obj/9mmclip")->eventMove(this_object());
    }
    return 1;
}
void init(){
    ::init();
}
