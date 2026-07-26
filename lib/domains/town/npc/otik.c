#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;

protected void create() {
    ::create();
    SetKeyName("otik");
    SetId( ({ "vendor","otik", "owner", "shopkeep", "shopkeeper", "keeper" }) );
    SetShort("店主奥提克");
    SetLevel(12);
    SetLong("奥提克是当地杂货店的老板，这是镇中心一家古老而著名的"+
            "贸易站。他是拉尔斯的兄弟，同样是一个低调的家伙，同样快活。");
    SetGender("male");
    SetMorality(40);
    SetRace("human");
    AddCurrency("electrum", random(200));
    SetSkill("bargaining", 1);
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetStorageRoom("/domains/town/room/shop2");
    SetMaxItems(10000);
    SetVendorType(VT_ALL);
    SetAttackable(0);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init(){
    ::init();
}
