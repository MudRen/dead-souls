#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather boot");
    SetAdjectives( ({"leather", "simple", "orc", "orcish", "protective","leg","right","full leg"}) );
    SetId(({"boot","right boot"}));
    SetShort("一只皮靴");
    SetLong("一只兽人设计的厚皮长靴，简单但防护性不错。设计用于右脚和右腿。");
    SetMass(120);
    SetBaseCost("silver", 200);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,10);
    SetProtection(KNIFE,10);
    SetArmorType(A_LONG_BOOT);
    SetRestrictLimbs(({"right foot","right leg"}));
}

void init(){
    ::init();
}
