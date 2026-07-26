#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("naiad");
    SetId( ({"nymph", "ludivine", "woman","spirit"}) );
    SetAdjectives(({"water", "beautiful"}));
    SetShort("一位美丽的水仙子");
    SetLong("这个苗条的自然精灵看起来是一位水仙子，守护着这个奇异的水池。");
    SetClass("fighter");
    SetLevel(8);
    SetMelee(1);
    SetRace("nymph");
    SetGender("female");
    SetGuard("down", "水仙子嬉闹地挡住了你的去路。");
}

void init(){
    ::init();
}
