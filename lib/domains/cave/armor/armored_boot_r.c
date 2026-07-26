#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("armored boot");
    SetAdjectives( ({"armored", "orc", "orcish", "protective"}) );
    SetId(({"boot","right boot"}));
    SetShort("一只装甲靴");
    SetLong("这是一只兽人设计的装甲靴，设计用来覆盖右脚和右腿，看起来极其耐用且防护性强。");
    SetMass(60);
    SetBaseCost("silver", 300);
    SetProtection(BLUNT,15);
    SetProtection(BLADE,15);
    SetProtection(KNIFE,15);
    SetArmorType(A_LONG_BOOT);
    SetRestrictLimbs(({"right foot","right leg"}));
}

void init(){
    ::init();
}
