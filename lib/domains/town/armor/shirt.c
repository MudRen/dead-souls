#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("a white t-shirt");
    SetId(({"shirt","tshirt","t-shirt","t shirt"}));
    SetAdjectives(({"white"}));
    SetShort("一件白色T恤");
    SetLong("一件普通的白色T恤。");
    SetMass(2);
    SetBaseCost("silver",1);
    SetArmorType(A_SHIRT);
}

void init(){
    ::init();
}
