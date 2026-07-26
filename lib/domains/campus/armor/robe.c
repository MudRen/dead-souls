#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("wizard's robe");
    SetId(({"robe","cloak","duster"}));
    SetAdjectives(({"wizard","wizard's","soft"}));
    SetShort("长袍");
    SetLong("这是一件宽大舒适的长袍，像是巫师会穿的那种。");
    SetMass(75);
    SetDollarCost(100);
    SetDamagePoints(100);
    SetProtection(BLUNT,100);
    SetProtection(BLADE,100);
    SetProtection(KNIFE,100);
    SetArmorType(A_CLOAK);
}
void init(){
    ::init();
}
