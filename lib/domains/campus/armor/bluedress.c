#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("blue dress");
    SetId(({"dress","outfit","costume"}));
    SetAdjectives(({"blue","cotton","lovely","light"}));
    SetShort("可爱的蓝色连衣裙");
    SetLong("这是一件可爱的蓝色连衣裙，设计简洁实用，看起来既舒适又方便。裙摆到膝盖处，面料摸起来柔软轻盈却又结实，像是某种棉质材料。");
    SetMass(10);
    SetDollarCost(100);
    SetDamagePoints(100);
    SetArmorType(A_BODY_ARMOR);
}
