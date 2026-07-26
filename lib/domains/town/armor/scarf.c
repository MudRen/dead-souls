#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("scarf");
    SetId(({"scarf"}));
    SetAdjectives( ({"handsome","tartan"}) );
    SetShort("一条漂亮的格子围巾");
    SetLong("这是一条漂亮的围巾，非常舒适，而且很保暖。");
    SetMass(3);
    SetBaseCost("silver", 350);
    SetArmorType(A_COLLAR);
}

void init(){
    ::init();
}
