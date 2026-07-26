#include <lib.h>

inherit LIB_SENTIENT;
inherit LIB_MOUNT;
inherit LIB_DOMESTICATE;

protected void create() {
    sentient::create();
    SetKeyName("horse");
    SetId(({"horse","large horse"}));
    SetShort("一匹大马");
    SetLong("一匹大型有蹄四足动物，比你更高更壮。");
    SetWimpy(50);
    SetLevel(5);
    SetRace("horse");
    SetGender("male");
    SetMelee(1);
    SetAction(5, ({
                "马打了个响鼻。", "你听到马嘶鸣。",
                "马在空中甩了甩尾巴。",
                "马环顾四周。"}));
    SetNoClean(1);
}
void init(){
    ::init();
}
