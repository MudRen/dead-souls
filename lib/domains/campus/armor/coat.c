#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("lab coat");
    SetId(({"coat","labcoat"}));
    SetAdjectives(({"lab","science","white","long"}));
    SetShort("白大褂");
    SetLong("这是一件白色的长实验服，科学家们常穿这种衣服以避免把实验结果弄到自己身上。");
    SetMass(75);
    SetDollarCost(20);
    SetArmorType(A_CLOAK);
}
void init(){
    ::init();
}
