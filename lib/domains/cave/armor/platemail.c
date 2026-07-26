#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("suit of armor");
    SetId(({"armor","plate mail","platemail","suit","armor","suit of armor"}));
    SetAdjectives(({"full","plate","plated","metal"}));
    SetShort("一套全身铠甲");
    SetLong("这是一套巨大而沉重的全身铠甲，就是骑士穿的那种。厚实的金属护板提供了非凡的防护，而关节处的精细设计又保证了极大的活动自由。");
    SetMass(2500);
    SetBaseCost("silver",5000);
    SetProtection(BLUNT,20);
    SetProtection(BLADE,50);
    SetProtection(KNIFE,50);
    SetArmorType(A_BODY_ARMOR);
}

void init(){
    ::init();
}
