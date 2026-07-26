#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("sock");
    SetId(({"sock"}));
    SetAdjectives(({"black","nylon","knee-length","knee","knee length"}));
    SetShort("一只黑色长尼龙袜");
    SetLong("一只黑色尼龙及膝长袜。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_LONG_SOCK);
}

void init(){
    ::init();
}
