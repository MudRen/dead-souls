#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("boar");
    SetAdjectives( ({"huge", "tusked", "hairy", "deadly", "snorting", "sweaty", "ugly", "piggish"}) );
    SetId( ({"pig", "beast"}) );
    SetShort("一头野猪");
    SetLong("这只巨大的、长着獠牙、毛茸茸的野兽至少有一千磅重，充满了呼哧呼哧的、汗流浃背的攻击性。虽然它丑陋且像猪一样，但它对人来说和任何狮子、老虎或熊一样致命。");
    SetLevel(1);
    SetMelee(1);
    SetRace("pig");
    SetGender("male");
}
void init(){
    ::init();
}
