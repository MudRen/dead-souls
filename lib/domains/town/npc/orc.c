#include <lib.h>
#include <domains.h>

inherit LIB_NPC;
int lupus;

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
    if(!strsrch(base_name(environment()), DOMAIN_EX)){
        if(!lupus){
            lupus = 1;
            eventForce("say bad wolf!");
        }
        return 0;
    }
    else eventForce("growl at "+val->GetKeyName());
    return 1;
}

protected void create() {
    npc::create();
    SetKeyName("orc");
    SetId(({"orc"}));
    SetAdjectives(({"dirty"}));
    SetShort("一个肮脏的兽人");
    SetLong("这个兽人是其种族的典型代表：卑鄙、野蛮、矮小。它看起来像是一个幼年或青春期的兽人，因此危险性较低但更具敌意。");
    SetLevel(1);
    SetRace("orc");
    SetGender("male");
    SetMaxHealthPoints(100);
    SetEncounter(  (: CheckOrc :) );
    SetInventory(([
                "/domains/town/weap/dagger":"wield dagger",
                ]) );
    SetGuard("west", "一个兽人挡住了你的去路！" );
    SetGuard("north", "一个兽人挡住了你的去路！");
}
void init(){
    ::init();
}
void reset(){
}
