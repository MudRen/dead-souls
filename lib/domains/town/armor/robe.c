#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("wizard's robe");
    SetId(({"robe","cloak","duster"}));
    SetAdjectives(({"wizard","wizard's","soft"}));
    SetShort("一件长袍");
    SetLong("这是一件看起来很舒适的大袍子，像巫师穿的那种。");
    SetMass(200);
    SetBaseCost("silver",100);
    SetProtection(BLUNT,100);
    SetProtection(BLADE,100);
    SetProtection(KNIFE,100);
    SetArmorType(A_CLOAK);
}

void init(){
    ::init();
}
