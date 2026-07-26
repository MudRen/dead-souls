#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("wizard hat");
    SetId(({"hat","headgear"}));
    SetAdjectives(({"wizard","wizard's"}));
    SetShort("一顶巫师帽");
    SetLong("这是一顶宽边大软帽，尖顶，像巫师戴的那种。");
    SetMass(50);
    SetBaseCost("silver",500);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
}

void init(){
    ::init();
}
