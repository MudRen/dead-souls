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
    SetLong("这是一支轻便的小型投掷矛。");
    SetMass(50);
    SetVendorType(VT_WEAPON);
    SetClass(30);
    SetDamageType(PIERCE);
    SetWeaponType("projectile");
}

void init(){
    ::init();
    add_action("podcast","podcast");
}

int podcast(){
    write("不知为何，标枪现在似乎做不到那件事。");
    return 1;
}
