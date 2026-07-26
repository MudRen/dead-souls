#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("armor");
    SetId(({"armor"}));
    SetAdjectives(({"generic"}));
    SetShort("普通盔甲");
    SetLong("一件尺寸不定的普通盔甲。");
    SetMass(50);
    SetArmorType(A_SHIRT);
    SetProtection(KNIFE, 5);
    SetProtection(COLD, 5);
}
void init(){
    ::init();
}
