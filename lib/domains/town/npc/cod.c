#include <lib.h>
#include <position.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("fish");
    SetAdjectives( ({"cod", "medium", "unremarkable"}) );
    SetId(({"cod","codfish"}));
    SetShort("一条鱼");
    SetLong("一条中等大小的鳕鱼。");
    SetWanderSpeed(1);
    //Letting npc's load virtual rooms can be dangerous.
    //You were warned.
    //SetPermitLoad(1);
    SetPosition(POSITION_SWIMMING);
    SetPacifist(1);
    SetLevel(1);
    SetRace("fish");
    SetHealthPoints(10);
    SetMaxHealthPoints(10);
    SetGender("male");
}
void init(){
    ::init();
}
