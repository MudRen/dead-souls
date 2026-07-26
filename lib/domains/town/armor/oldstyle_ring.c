#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("metal ring");
    SetId(({"ring"}));
    SetAdjectives( ({"simple","metal"}) );
    SetShort("一枚简单的戒指");
    SetLong("这是一枚简单的戒指。");
    SetMass(1);
    SetValue(100);
    SetArmorType(A_RING);
}

void init(){
    ::init();
}
