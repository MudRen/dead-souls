#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;


protected void create(){
    armor::create();
    SetKeyName("gold necklace");
    SetId(({"necklace"}));
    SetAdjectives( ({"gold","beautiful"}) );
    SetShort("金项链");
    SetLong("这是一条简洁而美丽的金项链。");
    SetMass(1);
    SetDollarCost(5000);
    SetDamagePoints(100);
    SetArmorType(A_COLLAR);
}
void init(){
    ::init();
}
