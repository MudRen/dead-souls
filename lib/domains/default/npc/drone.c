#include <lib.h>
#include ROOMS_H
#include <position.h>

inherit LIB_SENTIENT;

protected void create() {
    sentient::create();
    SetKeyName("drone");
    SetAdjectives( ({"small","metal"}) );
    SetId( ({"drone","bot","robot"}) );
    SetShort("一个小型无人机");
    SetLong("一个小型金属球体。");
    SetLevel(1);
    SetInvis(1);
    SetMaxHealthPoints(50000);
    SetRace("bot");
    SetGender("neuter");
    SetClass("explorer");
    SetWanderSpeed(1);
    SetPermitLoad(1);
    SetEncounter(0);
    SetPosition(POSITION_FLYING);
    SetNoClean(1);
    SetPacifist(1);
    SetWimpy(99);
}

int eventReceiveDamage(mixed args...){
    return 0;
}

int eventMove(mixed dest){
    int ret;
    object env = environment();     
    string location;

    if(!env) location = ROOM_START;     
    else if(clonep(env)) location = file_name(env);
    else location = base_name(env);

    if(location) this_object()->SetProperty("LastLocation", location); 
    ret = ::eventMove(dest);
    AddStaminaPoints(GetMaxStaminaPoints());
    return ret;
}

void init(){
    ::init();
}
