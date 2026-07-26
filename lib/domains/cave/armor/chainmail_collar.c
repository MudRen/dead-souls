#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("collar");
    SetId(({"neck guard","guard"}));
    SetAdjectives( ({"neck","collar","chainmail"}) );
    SetShort("一个锁子甲护颈");
    SetLong("这是一个简单的锁子甲护颈，用来保护颈部免受武器伤害。");
    SetMass(50);
    SetArmorType(A_COLLAR);
    SetProtection(BLUNT,4);
    SetProtection(BLADE,25);
    SetProtection(KNIFE,25);
}

void init(){
    ::init();
}
