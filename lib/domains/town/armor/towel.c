#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
inherit LIB_ARMOR;

protected void create(){
    armor::create();
    SetKeyName("damp towel");
    SetId(({"towel"}));
    SetAdjectives(({"damp","bath","ordinary", "bathtowel"}));
    SetShort("一条湿毛巾");
    SetLong("这是一条普通的浴巾。");
    SetMass(25);
    SetBaseCost("silver",10);
    SetProtection(BLUNT,1);
    SetProtection(BLADE,1);
    SetProtection(KNIFE,1);
    SetArmorType(A_PANTS);
}

void init(){
    ::init();
}
