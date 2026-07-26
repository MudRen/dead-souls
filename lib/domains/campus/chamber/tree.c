#include <lib.h>
#include <climb.h>
#include <position.h>

inherit LIB_CHAMBER;
inherit LIB_CLIMB;

varargs mixed ClimbMe(mixed args...){
    return 1;
}

protected void create() {
    ::create();
    SetKeyName("tree");
    SetId(({"oak"}));
    SetAdjectives(({"large"}));
    SetShort("一棵大树");
    SetLong("这是一棵非常大的树。它在虚拟校区出现之前就已经存在了，看起来在虚拟校区消失之后它还会继续存在。");
    SetChamberInterior("你在大学广场这棵大树粗壮的枝干之间。");
    SetRace("tree");
    SetPacifist(1);
    SetPosition(POSITION_NULL);
    SetMelee(0);
    SetNoClean(1);
    SetMount(1);
    SetMountStyle("driven");
    SetVisibleRiders(0);
    SetOpacity(0);
    SetMaxHealthPoints(20);
    SetMaxCarry(30000);
    SetNoCondition(1);
    SetAttackable(0);
    SetClimb( (: ClimbMe :), CLIMB_DOWN );
    SetClimb( (: ClimbMe :), CLIMB_OUT );
    SetClimb( (: ClimbMe :), CLIMB_UP );
    SetClimb( (: ClimbMe :), CLIMB_INTO );
    SetClimb( (: ClimbMe :), CLIMB_THROUGH );
}

void init(){
    ::init();
}

varargs mixed eventClimb(object who, int type, string where){
    mixed ret;
    switch(type){
        case CLIMB_DOWN:
            ret = eventDismount(who);
            break;
        case CLIMB_OUT:
            ret = eventDismount(who);
            break;
        default :
            ret = eventMount(who);
            break;
    }
    return ret;
}
