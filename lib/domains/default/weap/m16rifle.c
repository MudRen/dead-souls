#include <lib.h>
#include <vendor_types.h>
#include <damage_types.h>
inherit LIB_FIREARM;
void create(){
    ::create();
    SetKeyName("rifle");
    SetId(({"rifle","m16","M-16","weapon"}));
    SetAdjectives(({"m-16","M-16","m16","M16","assault","colt"}));
    SetShort("一把M-16突击步枪");
    SetLong("这把流线型黑色武器数十年来一直是军队的主力装备。"+
            "它耐用、精准，最重要的是，极具杀伤力。"+
            "这把步枪使用.223口径弹匣。");
    SetCaliber(223);
    SetFirearmType("auto");
    SetFirearmName("rifle");
    SetAmmoType("nato");
    SetMass(60);
    SetDollarCost(1000);
    SetHands(2);
    SetClass(20);
    SetWeaponType("blunt");
    SetDamageType(BLUNT);
    SetVendorType(VT_WEAPON);
}

void init(){
    ::init();
}
