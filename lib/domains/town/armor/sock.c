#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("sock");
    SetId(({"sock"}));
    SetAdjectives(({"white","cotton","athletic"}));
    SetShort("一只白色棉袜");
    SetLong("一只白色棉质运动袜。");
    SetMass(5);
    SetBaseCost("silver",1);
    SetArmorType(A_SOCK);
}

void init(){
    ::init();
}
