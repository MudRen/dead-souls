#include <lib.h>
#include <position.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("fish");
    SetAdjectives( ({"grouper", "large", "tall","flat"}) );
    SetId(({"grouper"}));
    SetShort("一条石斑鱼");
    SetLong("一条非常大的鱼，有一张巨大的嘴和奇特的高大扁平身体。");
    SetWanderSpeed(3);
    //Letting npc's load virtual rooms can be dangerous.
    //You were warned.
    //SetPermitLoad(1);
    SetPosition(POSITION_SWIMMING);
    SetPacifist(1);
    SetLevel(10);
    SetRace("fish");
    SetGender("male");
}
void init(){
    ::init();
}
