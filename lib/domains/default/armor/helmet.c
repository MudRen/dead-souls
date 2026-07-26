#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;
protected void create(){
    armor::create();
    SetKeyName("steel helmet");
    SetId(({"helmet","cover","steel"}));
    SetAdjectives(({"steel","battle","hard"}));
    SetShort("一顶钢盔");
    SetLong("这是一顶由坚韧金属制成的头盔。");
    SetMass(180);
    SetBaseCost("silver",500);
    SetDamagePoints(100);
    SetArmorType(A_HELMET);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
}
