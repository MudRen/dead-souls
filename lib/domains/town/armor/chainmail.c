#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("chainmail shirt");
    SetId(({"armor","chainmail","mail","shirt","chain mail"}));
    SetAdjectives(({"chainmail","sturdy","sturdy-looking","chain mail"}));
    SetShort("一件结实的锁子甲");
    SetLong("这是一件由小而薄的金属环连接而成的盔甲衬衫。");
    SetMass(200);
    SetBaseCost("silver",800);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,20);
    SetProtection(KNIFE,20);
    SetArmorType(A_ARMOR);
}

void init(){
    ::init();
}
