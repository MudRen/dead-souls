#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("gold_ring");
    SetId(({"ring","gold ring"}));
    SetAdjectives( ({"beautiful"}) );
    SetShort("美丽的金戒指");
    SetLong("这是一枚简洁而美丽的金戒指，适合戴在手指上。");
    SetMass(1);
    SetDollarCost(1000);
    SetDamagePoints(100);
    SetArmorType(A_RING);
}
void init(){
    ::init();
}
