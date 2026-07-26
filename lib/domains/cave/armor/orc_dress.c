#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("dress");
    SetId(({"dress"}));
    SetAdjectives(({"improvised","simple"}));
    SetShort("一条简陋的裙子");
    SetLong("这是一条用边角料临时拼凑的简陋小裙子。");
    SetMass(10);
    SetBaseCost("silver",1);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
