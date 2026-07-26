#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_WORN_STORAGE;

protected void create(){
    ::create();
    SetKeyName("generic worn storage");
    SetId(({"thing","worn_storage","storage","article"}));
    SetAdjectives(({"article of","generic","worn"}));
    SetShort("普通穿戴式储物装备");
    SetLong("这是一件可以穿戴的装备，也可以容纳物品。");
    SetCanClose(1);
    SetMaxCarry(100);
    SetMass(200);
    SetBaseCost("silver",10);
    SetDamagePoints(100);
    SetArmorType(A_PANTS);
    SetProtection(COLD, 1);
}
void init(){
    ::init();
}
