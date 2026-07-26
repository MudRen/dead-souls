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
    SetLong("这是一套非常大且重的盔甲，那种只有最强大的战士才能穿戴的类型。它散发着魔法光芒。");
    SetMass(900);
    SetBaseCost("silver",10000);
    SetDamagePoints(100);
    SetProtection(BLUNT,40);
    SetProtection(BLADE,60);
    SetProtection(KNIFE,60);
    SetProtection(PIERCE,60);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
