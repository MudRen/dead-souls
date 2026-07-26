#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("healer's toga");
    SetId(({"toga"}));
    SetAdjectives(({"long","white","comfotable"}));
    SetShort("一件白色长袍");
    SetLong("这是一件舒适的全长袍。是那种古罗马人穿的款式。");
    SetMass(75);
    SetBaseCost("silver",100);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,10);
    SetProtection(KNIFE,10);
    SetArmorType(A_CLOAK);
}

void init(){
    ::init();
}
