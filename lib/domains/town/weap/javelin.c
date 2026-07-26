#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("javelin");
    SetAdjectives( ({"throwing", "small", "light"}) );
    SetId( ({"spear"}) );
    SetShort("一支标枪");
    SetLong("这是一支轻便的小投枪。");
    SetMass(50);
    SetVendorType(VT_WEAPON);
    SetClass(30);
    SetDamageType(PIERCE);
    SetWeaponType("projectile");
    SetBaseCost("silver", 85);
}

void init(){
    ::init();
    add_action("podcast","podcast");
}

int podcast(){
    write("不知为何，标枪现在似乎无法那样做。");
    return 1;
}
