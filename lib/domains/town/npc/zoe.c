#include <lib.h>
#include <vendor_types.h>

inherit LIB_TELLER;


protected void create() {
    ::create();
    SetKeyName("zoe");
    SetId( ({ "teller","banker","executive","shawty" }) );
    SetAdjectives( ({ "bank","executive","friendly","efficient" }) );
    SetShort("银行出纳佐伊");
    SetLevel(12);
    SetLong("佐伊是一位迷人的年轻金发女郎，"+
            "带着法国口音。她穿着保守的行政风格服装，"+
            "给人一种友好而高效的感觉。");
    SetGender("female");
    SetMorality(40);
    SetRace("human");
    AddCurrency("silver", random(100));
    SetProperty("no bump", 1);
    SetBankName("First Village Bank");
    SetLocalCurrency("silver");
    SetLocalFee(1);
    SetOpenFee(5);
    SetExchangeFee(2);
    SetCurrencies( ({ "dollars", "copper", "silver", "electrum", "gold", "platinum" }) );
    SetPolyglot(1);
    SetLanguage("common", 100);
    SetDefaultLanguage("common");
}
void init(){
    ::init();
}
