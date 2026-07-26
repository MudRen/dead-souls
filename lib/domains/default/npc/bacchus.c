#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("bacchus");
    SetAdjectives( ({"roman", "drunk"}) );
    SetId( ({"god", "god of wine", "dionysos", "dionysus"}) );
    SetShort("巴克斯，罗马酒神");
    SetLong("罗马酒神如何找到这里是一个谜，可能连他自己也不知道。此刻他似乎急需睡一觉来消除最近的放纵。他得自己想办法解释为什么会在一群动物中醒来，还带着宿醉。");
    SetLevel(200);
    SetMelee(1);
    SetRace("god");
    SetGender("male");
    SetSleeping(500);
}
void init(){
    ::init();
}
