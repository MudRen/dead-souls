#include <lib.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("mock turtle");
    SetAdjectives( ({"peculiar", "mock"}) );
    SetId( ({"turtle", "tortoise"}) );
    SetShort("一只假海龟");
    SetLong("这种奇特的生物有着小牛的头但却是海龟的身体。");
    SetLevel(1);
    SetMelee(1);
    SetRace("tortoise");
    SetGender("male");
}
void init(){
    ::init();
}
