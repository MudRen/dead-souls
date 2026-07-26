#include <lib.h>
#include <damage_types.h>
inherit LIB_ITEM;

create() {
    ::create();
    SetId( ({ "dagger", "rusty dagger" }) );
    SetKeyName("dagger");
    SetShort("一把生锈的匕首");
    SetLong("一把被人扔掉的旧匕首。\n");
    SetMass(350);   SetValue( 25);
    SetDamageType(KNIFE);
    SetClass(7);
    SetWeaponType("knife");
    SetWield("虽然恶心，但还是能用。");
}
