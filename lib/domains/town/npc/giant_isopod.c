#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("isopod");
    SetAdjectives( ({"huge", "giant"}) );
    SetId(({"arthropod","creature"}));
    SetShort("一只巨型等足虫");
    SetLong("这是一只两米长的节肢动物，这种巨大的生物长着钳爪、多条肢体，以及一个对大多数类人生物来说十分丑陋的带颚头部。");
    SetMelee(1);
    SetLevel(1);
    SetRace("isopod");
    SetClass("explorer");
    SetGender("female");
    SetEncounter(100);
    SetGuard("up", "巨型等足虫挡住了你的去路！");
}
void init(){
    ::init();
}
