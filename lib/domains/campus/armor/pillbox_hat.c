#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("pillbox hat");
    SetId(({"hat"}));
    SetAdjectives(({"pillbox"}));
    SetShort("浅蓝色药盒帽");
    SetLong("一顶可爱的浅蓝色药盒帽。内衬看起来是豹皮的。看起来不太舒服。");
    SetMass(50);
    SetDollarCost(50);
    SetDamagePoints(10);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 2);
    SetProtection(BLADE, 2);
    SetProtection(KNIFE, 2);
}
