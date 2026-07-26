#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("avidryl");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个鸟人");
    SetLong("这就是传说中的鸟人。他非常像人类，大约六英尺高，体格健壮。他看起来甚至可能与克林贡人不相上下。他最引人注目的是背上两只巨大的鸟形翅膀，用于飞行。");
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
