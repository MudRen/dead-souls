#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("avidryl");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort="一个鸟人");
    SetLong("这就是传说中的鸟人。他非常 humanoid，大约六英尺高，体格 robust。他看起来 might even be a match for a Klingon。 The most striking thing about him are the two large birdlike wings on his back, used for flying。");
    SetAutoStand(1);
    SetPosition(POSITION_FLYING);
    SetClass("explorer");
    SetLevel(5);
    SetRace("avidryl");
    SetGender("male");
}
void init(){
    ::init();
}
