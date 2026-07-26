#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("kevlar helmet");
    SetId(({"helmet","cover","kevlar"}));
    SetAdjectives(({"kevlar","battle","hard"}));
    SetShort("一顶迷彩凯夫拉头盔");
    SetLong("这是一顶军用头盔，由非常坚硬的凯夫拉材料制成。");
    SetMass(50);
    SetBaseCost("silver",500);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 25);
    SetProtection(BLADE, 25);
    SetProtection(KNIFE, 25);
    SetProtection(PIERCE, 25);
}

void init(){
    ::init();
}
