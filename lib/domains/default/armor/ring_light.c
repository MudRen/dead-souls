#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("ring");
    SetId(({"ring"}));
    SetAdjectives( ({"magic","magical","glowing","light","glowing"}) );
    SetShort("一枚璀璨发光的戒指");
    SetLong("这枚魔法戒指散发出非常明亮的光芒，"+
            "足以照亮整个房间。");
    SetRadiantLight(30);
    SetMass(1);
    SetBaseCost("silver",5000);
    SetArmorType(A_RING);
}

void init(){
    ::init();
}
