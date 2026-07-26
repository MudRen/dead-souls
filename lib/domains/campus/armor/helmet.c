#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("kevlar helmet");
    SetId(({"helmet","cover","kevlar"}));
    SetAdjectives(({"kevlar","battle","hard"}));
    SetShort("迷彩凯夫拉头盔");
    SetLong("这是一顶由非常坚固的聚合物纤维制成的军用头盔，能提供出色的防弹保护。表面有斑驳的迷彩设计，有助于在树林中隐蔽。");
    SetMass(50);
    SetDollarCost(500);
    SetDamagePoints(100);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
}
