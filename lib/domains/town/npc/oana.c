#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;


protected void create() {
    ::create();
    SetKeyName("oana");
    SetId( ({ "shopkeep","shopkeeper","keeper","vendor"}) );
    SetAdjectives( ({ "friendly","sprightly","plain","simple" }) );
    SetShort("魔法商店店主奥安娜");
    SetLevel(12);
    SetLong("奥安娜是一个活泼的年轻女子，留着很短的"+
            "深色头发，穿着朴素简单。她是魔法商店"+
            "的店主，你可以和她交易魔法物品。");
    SetGender("female");
    SetMorality(40);
    SetRace("human");
    AddCurrency("silver", random(100));
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetStorageRoom("/domains/town/room/magic_shop2");
    SetMaxItems(10000);
    SetVendorType(VT_MAGIC);
    SetSkill("bargaining", 1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init(){
    ::init();
}
