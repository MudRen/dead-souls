#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("motorcycle helmet");
    SetId(({"helmet","cover","motorcycle"}));
    SetAdjectives(({"motorcycle","battle","hard"}));
    SetShort("一顶黑色摩托车头盔");
    SetLong("这是一顶由坚硬复合材料制成的头盔。");
    SetMass(50);
    SetBaseCost("silver",200);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
    SetProtection(PIERCE, 20);
}

void init(){
    ::init();
}
