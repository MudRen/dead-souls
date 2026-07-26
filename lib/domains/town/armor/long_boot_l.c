#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("riding boot");
    SetId(({"boot"}));
    SetAdjectives(({"long","riding","black","leather","left"}));
    SetShort("一只长骑马靴");
    SetLong("一只黑色皮革长骑马靴。适合左脚。");
    SetMass(40);
    SetBaseCost("silver",75);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_LONG_BOOT);
    SetRestrictLimbs(({"left foot","left leg"}));
}

void init(){
    ::init();
}
