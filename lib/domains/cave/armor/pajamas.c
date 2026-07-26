#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <size_types.h>
inherit LIB_ARMOR;

protected void create(){
    ::create();
    SetKeyName("pajamas");
    SetId(({"pj","pjs", "peejays"}));
    SetAdjectives(({"small","tiny","pair of","set of",
                "bloodstained", "blood stained", "stained"}));
    SetShort("小小的、血迹斑斑的睡衣");
    SetLong("这是一套非常小的睡衣，上面沾满了干涸的血迹。");
    SetItems( ([
                ({"blood","crusted blood", "old, crusted blood"}) : "看起来穿这些睡衣的人曾遭受过可怕的伤害。",
                ]) );
    SetMass(2);
    SetBaseCost("silver",1);
    SetArmorType(A_BODY_ARMOR);
    SetSize(S_SOMEWHAT_SMALL|S_SMALL);
}

void init(){
    ::init();
}
