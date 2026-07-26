#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("blue jeans");
    SetId(({"jeans","pants","blue jeans","bluejeans","denim"}));
    SetAdjectives(({"blue","denim","comfortable","broken in","broken-in"}));
    SetShort("一条蓝色牛仔裤");
    SetLong("一条舒适的蓝色牛仔裤。");
    SetMass(20);
    SetBaseCost("silver",1);
    SetArmorType(A_PANTS);
}

void init(){
    ::init();
}
