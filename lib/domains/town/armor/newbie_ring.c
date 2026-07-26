#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("gold ring");
    SetId(({"ring","gold ring"}));
    SetAdjectives( ({"beautiful"}) );
    SetShort("一枚美丽的金戒指");
    SetLong("这是一枚简单而美丽的戒指，由黄金制成。新手可以从中获得一些保护。");
    SetMass(1);
    SetBaseCost("silver",500);
    SetArmorType(A_RING);
}

void init(){
    ::init();
}
