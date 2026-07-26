#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("suit of armor");
    SetId(({"armor","plate mail","platemail","suit","armor","suit of armor"}));
    SetAdjectives(({"full","plate","plated","metal"}));
    SetShort("一套全身盔甲");
    SetLong("这是一套非常大且重的盔甲，那种只有最强大的战士才能穿戴的类型。");
    SetMass(1000);
    SetBaseCost("silver",10000);
    SetProtection(BLUNT,60);
    SetProtection(BLADE,90);
    SetProtection(KNIFE,90);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
