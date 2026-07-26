#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather jacket");
    SetId(({"jacket"}));
    SetAdjectives(({"black","leather"}));
    SetShort("一件黑色皮夹克");
    SetLong("这是一件黑色皮革夹克。");
    SetMass(50);
    SetBaseCost("silver",100);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,2);
    SetProtection(KNIFE,5);
    SetArmorType(A_ARMOR);
}

void init(){
    ::init();
}
