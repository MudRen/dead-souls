#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("unicorn");
    SetId(({"unicorn","large unicorn"}));
    SetShort("一只美丽的白色独角兽");
    SetLong("这只白色独角兽是一匹高大骄傲的马，头上长着一只象牙色的角。长期以来一直是男性气概的象征，许多人仍然没有把这只长着长而硬的角的大型强壮野兽视为它所代表的强大性象征。");
    SetLevel(5);
    SetRace("unicorn");
    SetGender("male");
    SetMelee(1);
    SetAction(5, ({
                "独角兽打了个响鼻。", "你听到独角兽嘶鸣。",
                "独角兽在空中甩了甩尾巴。",
                "独角兽环顾四周。"}));
}
void init(){
    ::init();
}
