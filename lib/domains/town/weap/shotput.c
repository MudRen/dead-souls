#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("shot ball");
    SetAdjectives( ({"ball of", "palm sized", "shot"}) );
    SetId( ({"ball", "lead", "shot", "shotput"}) );
    SetShort("一个掌心大小的铅球");
    SetLong("这是一个铅球，直径约九英寸。这是一种叫做'铅球'的武器，用来投向敌人。");
    SetMass(50);
    SetVendorType(VT_WEAPON);
    SetClass(30);
    SetDamageType(BLUNT);
    SetWeaponType("projectile");
}
void init(){
    ::init();
}
