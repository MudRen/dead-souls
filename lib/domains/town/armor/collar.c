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
    SetShort("一个塑料项圈");
    SetLong("这是一个由柔软白色塑料制成的简单项圈。它能保护脖子免受伤害。");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetRead("Disease and parasite repellent collar, test character use only.");
    SetMass(10);
    SetArmorType(A_COLLAR);
    SetBane(({"all"}));
}

void init(){
    ::init();
}
