#include <lib.h>
#include <damage_types.h>
#include <vendor_types.h>

inherit LIB_ITEM;
protected void create(){
    item::create();
    SetKeyName("rod");
    SetId( ({ "staff", "stick", "pole" , "rod of asclepius", "rod of aesculapius"}) );
    SetAdjectives( ({ "wood","wooden" }) );
    SetShort("一根雕蛇木杖");
    SetLong("这根漂亮的法杖被雕刻成蛇的形状。它看起来很神秘。");
    SetVendorType(VT_WEAPON);
    SetDamagePoints(50);
    SetClass(100);
    SetBaseCost("silver",250);
    SetMass(100);
    SetWeaponType("blunt");
    SetHands(2);
    SetDamageType(BLUNT);
}
