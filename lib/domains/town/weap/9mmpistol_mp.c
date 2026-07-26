#include <lib.h>
#include <vendor_types.h>
inherit "/lib/pistol";
int AddClip();
void CheckMP();
void create(){
    pistol::create();
    SetKeyName("gun");
    SetId(({"gun","pistol"}));
    SetAdjectives(({"9mm","automatic","9 millimeter","semiautomatic"}));
    SetShort("一把9毫米半自动手枪");
    SetLong("这是一把大型半自动手枪，发射9毫米子弹。它很可靠，精度也不错。");
    SetMillimeter(9);
    SetFirearmType("auto");
    SetAmmoType("acp");
    SetMass(30);
    SetBaseCost("silver",3000);
    SetVendorType(VT_WEAPON);
}

void init() {
    pistol::init();
    CheckMP();
}

int AddClip(){
    new("/domains/town/obj/9mmclip")->eventMove(this_object());
    return 1;
}

void CheckMP(){
    if(base_name(environment(this_object())) == "/domains/town/npc/mp"){
        AddClip();
        SetLoaded(1);
        SetAmmo(15);
        SetMag(1);
    }
}
