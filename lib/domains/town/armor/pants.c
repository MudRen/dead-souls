#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather pants");
    SetId(({"pants"}));
    SetAdjectives(({"strong","leather","black","tough"}));
    SetShort("一条皮裤");
    SetLong("这些是由结实皮革制成的裤子。");
    SetMass(150);
    SetBaseCost("silver",110);
    SetProtection(BLADE,10);
    SetProtection(KNIFE,10);
    SetArmorType(A_PANTS);
}

void init(){
    ::init();
}
