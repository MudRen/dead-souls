#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather vest");
    SetAdjectives( ({"vest", "leather", "sturdy", "protective"}) );
    SetId(({"vest"}));
    SetShort("一件皮背心");
    SetLong("一件结实的皮背心，为躯干提供保护和保暖，同时允许手臂自由活动。");
    SetMass(50);
    SetBaseCost("silver", 100);
    SetArmorType(A_VEST);
    SetProtection(COLD, 10);
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 5);
    SetProtection(KNIFE, 5);
}

void init(){
    ::init();
}
