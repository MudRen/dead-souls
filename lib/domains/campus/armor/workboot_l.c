#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("workboot");
    SetAdjectives( ({"strong", "brown", "leather", "left", "work", "heavy"}) );
    SetId( ({"boot"}) );
    SetShort("棕色皮工作靴");
    SetLong("一只厚重的棕色皮工作靴，脚踝和鞋底支撑力强。设计为左脚穿着。");
    SetMass(40);
    SetBaseCost("silver",25);
    SetProtection(BLUNT,5);
    SetProtection(BLADE,5);
    SetProtection(KNIFE,5);
    SetArmorType(A_BOOT);
    SetRestrictLimbs(({"left foot"}));
}

void init(){
    ::init();
}
