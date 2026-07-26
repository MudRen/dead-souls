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
    SetLong("佐伊是一个迷人的年轻金发女郎，有着法国口音。她穿着保守的行政风格服装，散发着友好而高效的气质。");
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
