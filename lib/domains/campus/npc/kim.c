#include <lib.h>
#include <vendor_types.h>

inherit LIB_VENDOR;

protected void create() {
    vendor::create();
    SetKeyName("kim");
    SetId(({"vendor","kim","Kim","kimmie","employee","bookstore employee"}));
    SetShort("金，书店店员");
    SetLong("金是一个二十多岁的大学生，努力赚钱支付学费和养活自己。她看起来很友好，她明亮的蓝眼睛似乎在对你微笑。你也许可以从她这里买些东西，因为这是她的工作，或者她甚至可能从你这里买东西，如果她认为值钱的话。不过，如果你没有足够的钱，不要试图买东西……她看起来在必要时可以很认真。");
    SetInventory(([
                "/domains/campus/armor/collar" : "wear collar on neck",
                "/domains/campus/armor/jeans" : "wear jeans",
                "/domains/campus/armor/shirt" : "wear shirt",
                ]));
    SetLevel(1);
    SetRace("human");
    SetLanguage("common", 100);
    SetSkill("bargaining", 1);
    SetGender("female");
    SetLocalCurrency("dollars");
    SetStorageRoom("/domains/campus/room/bookstore2");
    SetMaxItems(10000);
    SetVendorType(VT_TREASURE | VT_ARMOR);
    SetGuard("/domains/campus/obj/register","Kim prevents your theft.");
}
void init(){
    ::init();
}
