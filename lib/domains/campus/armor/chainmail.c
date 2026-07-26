#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("chainmail shirt");
    SetId(({"armor","chainmail armor","chain mail armor","shirt","chainmail shirt","chainmail","chain mail shirt"}));
    SetShort("结实的锁子甲衬衫");
    SetLong("这是一件由金属环串联而成的锁子甲衬衫。");
    SetMass(75);
    SetDollarCost(100);
    SetDamagePoints(100);
    SetProtection(BLUNT,4);
    SetProtection(BLADE,25);
    SetProtection(KNIFE,25);
    SetArmorType(A_BODY_ARMOR);
}
