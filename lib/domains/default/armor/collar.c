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
    SetLong("这是一个由柔软的白色塑料制成的简单项圈。它似乎涂有一层细腻的透明树脂。项圈上写着一些字。");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetRead("疾病和寄生虫防护项圈，仅限测试角色使用。");
    SetMass(10);
    SetBaseCost("silver", 10);
    SetDamagePoints(100);
    SetArmorType(A_COLLAR);
    SetBane(({"all"}));
}
void init(){
    ::init();
}
