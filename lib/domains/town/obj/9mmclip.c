#include <lib.h>
#include <vendor_types.h>
inherit LIB_CLIP;

void create(){
    clip::create();
    SetKeyName("9mm clip");
    SetId(({"clip","magazine"}));
    SetAdjectives(({"9mm","ammunition","ammo","9 millimeter","pistol"}));
    SetShort("一个9毫米手枪弹夹");
    SetLong("这是一个细长的弹簧式金属容器，设计用于为9毫米手枪供弹。");
    SetMillimeter(9);
    SetMaxAmmo(15);
    SetAmmoType("acp");
    SetVendorType(VT_TREASURE);
    SetMass(5);
    SetBaseCost("silver", 45);
    SetInventory(([
                "/domains/town/obj/9mmround" : 15
                ]));
}

void init(){
    clip::init();
}
