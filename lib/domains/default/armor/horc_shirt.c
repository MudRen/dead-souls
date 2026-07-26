#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("shirt");
    SetAdjectives( ({"tee"}) );
    SetId( ({"t-shirt", "t shirt", "tshirt", "tee shirt"}) );
    SetShort("一件写着"我是半人类"的T恤");
    SetLong("一件尺寸不定的普通护甲。");
    SetMass(50);
    SetDamagePoints(100);
    SetArmorType(A_SHIRT);
    SetProtection(BLUNT, 20);
    SetProtection(BLADE, 20);
    SetProtection(KNIFE, 20);
}
void init(){
    ::init();
}
