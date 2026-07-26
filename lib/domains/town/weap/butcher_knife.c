#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("butcher knife");
    SetId( ({ "knife"}));
    SetAdjectives( ({ "sharp","razor sharp","steel","hefty","stainless","butcher"}));
    SetShort("一把8英寸屠宰刀");
    SetLong("这是一把8英寸屠宰刀。这把极其锋利的刀由锻造的高碳不锈钢制成。它结实、厚重，非常适合厨房工作，但可能不如切肉刀好用作武器。");
    SetMass(50);
    SetBaseCost("silver",95);
    SetVendorType(VT_WEAPON);
    SetClass(15);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}
int GetFancy(){
    return 1;
}
void init(){
    ::init();
}
