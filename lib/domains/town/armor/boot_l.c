#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather boot");
    SetId(({"boot","left boot"}));
    SetAdjectives(({"military","military-style","black","leather","combat"}));
    SetShort("一只黑色皮靴");
    SetLong("一只军用风格的战斗靴，黑色皮革制成。适合左脚。");
    SetMass(20);
    SetBaseCost("silver",25);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_BOOT);
    SetRestrictLimbs(({"left foot"}));
}

void init(){
    ::init();
}
