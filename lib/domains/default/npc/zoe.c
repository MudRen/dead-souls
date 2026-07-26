#include <lib.h>
#include <vendor_types.h>

inherit LIB_TELLER;


protected void create() {
    ::create();
    SetKeyName("zoe");
    SetId( ({ "teller","banker","executive" }) );
    SetAdjectives( ({ "bank","executive","friendly","efficient" }) );
    SetShort("银行出纳员佐伊");
    SetLevel(12);
    SetLong("佐伊是一个 attractive young blonde woman，有着法国口音。她 dressed in a conservative, executive style， and has a friendly and efficient air about her。");
    SetGender("female");
    SetMorality(40);
    SetRace("human");
    AddCurrency("silver", random(100));
    SetProperty("no bump", 1);
    SetLocalCurrency("silver");
    SetBankName("First Village Bank");
    SetLocalCurrency("silver");
    SetLocalFee(1);
    SetOpenFee(5);
    SetExchangeFee(2);
    SetCurrencies( ({ "copper", "silver", "electrum", "gold", "platinum" }) );


}
void init(){
    ::init();
}
