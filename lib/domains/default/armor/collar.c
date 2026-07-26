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
    SetLong="a plastic collar";
    SetLong("这是一个 simple collar made of a soft white plastic。它 seems to be coated with a fine, clear resin。 There is something written on the collar。");
    SetProperties(([
                "no steal" : 1,
                ]));
    SetRead("疾病和寄生虫 repellent 项圈，仅限测试角色使用。");
    SetMass(10);
    SetBaseCost("silver", 10);
    SetDamagePoints(100);
    SetArmorType(A_COLLAR);
    SetBane(({"all"}));
}
void init(){
    ::init();
}
