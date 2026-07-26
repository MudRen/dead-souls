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
    SetLong("This is a simple but beautiful ring made of "+
            "gold, suitable for wearing on one's finger.");
    SetMass(1);
    SetDollarCost(1000);
    SetDamagePoints(100);
    SetArmorType(A_RING);
}
void init(){
    ::init();
}
