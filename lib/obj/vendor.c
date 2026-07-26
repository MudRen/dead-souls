#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;

protected void create() {
    vendor::create();
    SetKeyName("vendor");
    SetId( ({ "shopkeep" }) );
    SetAdjectives( ({ "generic" }) );
    SetShort("普通商人");
    SetLevel(1);
    SetLong("一个不起眼的人，工作是出售物品。");
    SetGender("male");
    SetRace("human");
    SetSkill("bargaining", 1);
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetStorageRoom("/obj/room");
    SetMaxItems(100);
    SetVendorType(VT_ALL);
}
