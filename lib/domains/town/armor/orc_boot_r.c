#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("leather boot");
    SetAdjectives( ({"leather", "simple", "orc", "orcish", "inelegant", "protective"}) );
    SetId(({"boot","right boot"}));
    SetShort("一只皮靴");
    SetLong("一只兽人设计的皮靴。简单粗犷，但相当有防护力。适合右脚。");
    SetMass(60);
    SetBaseCost("silver", 30);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_BOOT);
    SetRestrictLimbs(({"right foot"}));
}

void init(){
    ::init();
}
