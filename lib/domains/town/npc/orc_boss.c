#include <lib.h>

inherit LIB_NPC;

int AllowPass(object who, object what){
    string *allowed_races = ({ "orc", "half-orc", "bear" });
    if(member_array(who->GetRace(), allowed_races) != -1) return 1;
    return ::AllowPass(who, what);
}

int CheckOrc(mixed val){
    string *allowed_races = ({ "orc", "half-orc", "bear" });
    if(!val) return 0;
    if(!objectp(val)) return 0;
    if(member_array(val->GetRace(), allowed_races) != -1) return 0;
    else eventForce("growl at "+val->GetKeyName());
    return 1;
}

protected void create() {
    npc::create();
    SetKeyName("boss orc");
    SetId(({"orc","boss","boss"}));
    SetAdjectives(({"dirty","orc","boss"}));
    SetShort("兽人首领");
    SetLong("这个兽人是其种族的典型代表：卑鄙、野蛮、矮小。它比你见过的当地兽人更大，看起来凶狠而坚韧。");
    SetLevel(1);
    SetRace("orc");
    SetClass("fighter");
    SetGender("male");
    SetMaxHealthPoints(200);
    SetEncounter(  (: CheckOrc :) );
    SetInventory(([
                "/domains/town/weap/dagger":"wield dagger",
                ]) );
    SetGuard("west","兽人首领挡住了你的去路！");
}

void init(){
    ::init();
}
