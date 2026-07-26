#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather pants");
    SetId(({"pants"}));
    SetAdjectives(({"strong","leather","black","tough"}));
    SetShort("皮裤");
    SetLong("这是用结实坚韧的皮革制成的裤子。");
    SetMass(150);
    SetBaseCost("silver",110);
    SetDamagePoints(10);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_PANTS);
}
void init(){
    ::init();
}
