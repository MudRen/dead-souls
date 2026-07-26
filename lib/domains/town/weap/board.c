#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("board of ed");
    SetId(({"board","board of ed","board of education"}));
    SetAdjectives(({"ed","education"}));
    SetShort("教育之板");
    SetLong("一块又长又宽的木板，一端有把手。看起来像是某种"教育工具"。");
    SetMass(50);
    SetBaseCost("silver",20);
    SetVendorType(VT_WEAPON);
    SetClass(20);
    SetDamageType(BLUNT);
    SetWeaponType("blunt");
}
