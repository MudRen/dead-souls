#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("leather boot");
    SetId(({"boot","leather boot"}));
    SetAdjectives( ({"leather","strong","tough","right"}) );
    SetShort("一只皮靴");
    SetLong("这是一只职业士兵的皮制战靴。 "+
            "它非常厚实坚固。设计为右脚穿着。");
    SetMass(50);
    SetBaseCost(50);
    SetDamagePoints(20);
    SetProtection(BLUNT,10);
    SetProtection(BLADE,20);
    SetProtection(KNIFE,20);
    SetArmorType(A_BOOT);
    SetRestrictLimbs(({"right foot"}));
}
