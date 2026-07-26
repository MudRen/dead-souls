#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("giant");
    SetAdjectives( ({"jolly", "green"}) );
    SetId(({"npc","mob","character","mobile"}));
    SetShort("一个绿巨人");
    SetLong("这个巨大的生物足有十五英尺高。不过他似乎并不敌对。事实上，只是相当 amused。他的皮肤完全是绿色的，他的衣服是由某种巨大的棕榈树叶制成的。");
    SetLevel(1);
    SetMelee(1);
    SetRace("giant");
    SetGender("male");
}
void init(){
    ::init();
}
