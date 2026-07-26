#include <lib.h>

inherit LIB_BOT;

protected void create() {
    ::create();
    SetKeyName("zookeeper bot");
    SetId( ({"bot", "robot", "zookeeper", "keeper"}) );
    SetAdjectives(({"non-player", "non player"}));
    SetShort("一个机器人饲养员");
    SetLong("这个高效的自动机器不断地喂养、清洗、梳理和照顾动物园里所有的野生动物。");
    SetLevel(1);
    SetMelee(1);
    SetRace("android");
    SetGender("male");
    SetMaxClones(3);
}
void init(){
    ::init();
}
