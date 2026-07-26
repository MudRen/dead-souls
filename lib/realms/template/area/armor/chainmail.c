#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("chainmail shirt");
    SetId(({"armor","chainmail","mail","shirt","chain mail"}));
    SetAdjectives(({"chainmail","sturdy","sturdy-looking","chain mail"}));
    SetShort("一件结实的锁子甲衬衫");
    SetLong("这是一件由小而薄的金属环串联而成的铠甲衬衫。");
    SetMass(500);
    SetBaseCost(1000);
    SetDamagePoints(100);
    SetProtection(BLUNT,4);
    SetProtection(BLADE,25);
    SetProtection(KNIFE,25);
    SetArmorType(A_ARMOR);
}
