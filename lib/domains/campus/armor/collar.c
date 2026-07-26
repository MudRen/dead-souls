#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
inherit LIB_BANE;

protected void create(){
    armor::create();
    SetKeyName("collar");
    SetId(({"repellent_collar","bane"}));
    SetAdjectives( ({"repellent","odd","plastic","white"}) );
    SetShort("塑料项圈");
    SetLong("这是一个由柔软的白色塑料制成的简单项圈。表面似乎涂有一层薄薄的透明树脂。项圈上写着一些字。");
    SetRead("Disease and parasite repellent collar, test character use only.");
    SetMass(1);
    SetDollarCost(5000);
    SetDamagePoints(100);
    SetArmorType(A_AMULET);
    SetBane(({"all"}));
}
