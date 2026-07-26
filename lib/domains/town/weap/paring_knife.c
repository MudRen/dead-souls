#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("paring knife");
    SetId( ({ "knife"}));
    SetAdjectives( ({ "serrated","sharp","razor sharp","steel","hefty","stainless","paring"}));
    SetShort("一把4英寸削皮刀");
    SetLong("这是一把4英寸削皮刀。这把非常锋利的刀由锻造的高碳不锈钢制成。虽然轻巧，但结实且平衡性好。");
    SetMass(20);
    SetBaseCost("silver",55);
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
