#include <position.h>
#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("moth");
    SetId(({"npc","mob","character","mobile"}));
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一只小飞蛾");
    SetLong("一种普通的飞虫，对旧衣服有特别的嗜好。");
    SetWimpy(80);
    SetPosition(POSITION_FLYING);
    SetLevel(1);
    SetMelee(1);
    SetRace("insect");
    SetMaxHealthPoints(2);
    SetGender("male");
}
void init(){
    ::init();
}
