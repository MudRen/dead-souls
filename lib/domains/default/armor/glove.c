#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ARMOR;


protected void create() {
    armor::create();
    SetKeyName("leather glove");
    SetId( ({ "glove" }) );
    SetAdjectives( ({ "black","leather","left" }) );
    SetShort("一只黑色皮手套");
    SetLong("一只五个手指的黑色手套。");
    SetDamagePoints(75);
    SetVendorType(VT_ARMOR);
    SetMass(10);
    SetBaseCost("silver",7);
    SetArmorType(A_GLOVE);
    SetProtection(BLUNT, 1);
    SetProtection(BLADE, 1);
    SetProtection(KNIFE, 2);
    SetProtection(HEAT, 3);
    SetProtection(COLD, 7);
    SetFingers(5);
}

void init(){
    ::init();
}
