#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("winged horse");
    SetId( ({"horse", "steed", "equine", "pegasus"}) );
    SetAdjectives( ({"flying", "winged", "white"}) );
    SetShort("一匹飞马");
    SetLong("这匹美丽的白色骏马是一匹飞马，一匹拥有巨大羽翼并能飞翔的马。");
    SetLevel(5);
    SetMount(1);
    SetRace("pegasus");
    SetStat("strength", 50);
    SetGender("male");
    SetMelee(1);
    SetAction(5, ({
                "飞马打了个响鼻。", "你听到飞马拍打了一下翅膀。",
                "飞马在空中甩了甩尾巴。",
                "飞马环顾四周。"}));
}
void init(){
    ::init();
}
