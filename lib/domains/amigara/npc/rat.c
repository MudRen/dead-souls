#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("rat");
    SetAdjectives( ({"ratlike","unusual","large","very","dangerous",
                "dangerous looking","rat like"}) );
    SetId( ({"rat","rous","beast"}) );
    SetShort("一只体型异常的啮齿动物");
    SetLong("一只非常大、看起来非常危险的鼠形野兽。");
    SetRace("rodent");
    SetGender("male");
    SetClass("fighter");
    SetEncounter(100);
    SetLevel(1);
    SetMelee(1);
    SetMessage("come","$N窜了进来。");
    SetMessage("leave","$N向$D窜去。");
    SetGuard("/domains/town/obj/ladder","那只老鼠龇牙咧嘴地挡住了你的尝试。");
}

void init(){
    ::init();
}

void heart_beat(){
    object env = environment();
    ::heart_beat();
}

