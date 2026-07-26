#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;

protected void create() {
    item::create();
    SetKeyName("carving knife");
    SetAdjectives( ({"8-inch", "serrated", "sharp", "razor-sharp", "razor", "steel", "hefty", "stainless", "carving"}) );
    SetId( ({ "knife"}));
    SetShort("一把锯齿8英寸切肉刀");
    SetLong("这是一把锯齿8英寸切肉刀。这把极其锋利的刀由锻造的高碳不锈钢制成。它非常适合切割肉类，同时也是一件不错的武器。");
    SetMass(50);
    SetBaseCost("silver",120);
    SetVendorType(VT_WEAPON);
    SetClass(20);
    SetDamageType(KNIFE);
    SetWeaponType("knife");
}
int GetFancy(){
    return 1;
}
void init(){
    ::init();
}
