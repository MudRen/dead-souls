#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("a mangy little rat");
    SetId(({"rat","dirty rat"}));
    SetShort("一只老鼠");
    SetLong("一只邋遢的小脏老鼠。");
    SetLevel(1);
    SetMaxHealthPoints(5);
    SetRace("rodent");
    SetGender("male");
    SetWanderSpeed(1);
    SetMessage("come","$N 窜了进来。");
    SetMessage("leave","$N 窜向$D。");
    SetAction(5, ({
                "老鼠吱吱叫了一声。", "你听到老鼠四处窜动的声音。",
                "一只邋遢的小老鼠蹭过你的腿。",
                "你听到细小的啃咬声。"}));
}
void init(){
    ::init();
}
