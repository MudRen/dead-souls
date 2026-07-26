#include <lib.h>
#include <vendor_types.h>
inherit LIB_ROUND;

void create(){
    round::create();
    SetKeyName(".50 round");
    SetId(({"round","bullet"}));
    SetAdjectives(({".50","caliber","rifle"}));
    SetShort("一颗.50口径步枪子弹");
    SetLong("这颗巨大的子弹将近五英寸长。任何被这大家伙击中的东西都得倒大霉。");
    SetCaliber(50);
    SetFirearmType("bolt");
    SetFirearmType("bolt");
    SetAmmoType("bolt");
    SetVendorType(VT_TREASURE);
    SetMass(1);
}
