#include <lib.h>
#include <vendor_types.h>
#include <damage_types.h>
#include <position.h>

inherit LIB_MISSILE;

int detonated;
int count, armed;
string *limbs,domain;
void analyze(string butt);
int HitLivings(object munch);
int radius = 0;
object *whom;

void create(){
    ::create();
    //SetKeyName("Poleekwa plasma rifle bolt");
    SetKeyName("plasma bolt");
    sscanf(base_name(this_object()),"/domains/%s/%*s",domain);
    SetId( ({"bolt","plasma"}) );
    SetAdjectives( ({"plasma", "energy"}) );
    SetShort("一枚等离子弹");
    SetLong("这是一个炽热物质形成的耀眼球体。");
    SetCruiseInMessage("一枚等离子弹从$D方向呼啸而来！");
    SetCruiseOutMessage("等离子弹向$D方向飞去。");
    SetMass(0);
    SetDollarCost(10);
    SetRange(20);
    SetSpeed(5);
    SetVendorType(VT_WEAPON);
    count=5;
    detonated=0;
}

int eventFall(){
    if(!armed) return ::eventFall();
    return 0;
}

void init(){
    ::init();
    if(armed){
        set_heart_beat(1);
        if(detonated==1) this_object()->eventDestruct();
    }
}

void heart_beat(){
    count--;
    if(detonated==1) this_object()->eventDestruct();
    if(count < 0){
        this_object()->detonate();
        return;
    }
    if(interactive(environment())){
        tell_object(environment(), "你正被等离子弹熔化。");
        return;
    }
    tell_object(environment(),"你听到低沉的嘶嘶声。");
    tell_object(environment(environment()), environment()->GetName()+"正被等离子弹熔化。");
}

int detonate(){
    object ob;
    string *stuffs;
    int num;
    ob = environment(this_object());
    ownerob = GetOwnerOb();
    if(living(ob)){
        stuffs=ob->GetLimbs();
        tell_object(ob, "\n你被等离子弹击中了！\n");
        tell_room(environment(ob), ob->GetName()+"被等离子弹击中了！\n",ob);
        this_object()->HitLivings(ob);
        detonated=2;
        if(ownerob) ownerob->ReportHit(ob);
    }
    else tell_room(room_environment(this_object()), "一枚等离子弹无害地爆炸了。");
    this_object()->eventDestruct();
    return 1;
}

mixed eventNegotiateObstacles(){
    object env = environment();
    if(!env) return 1;
    if(!inherits(LIB_ROOM,env)){
        detonate();
        return 0;
    }
    foreach(object ob in all_inventory(env)){
        if(living(ob) && ob->GetPosition() != POSITION_LYING){
            if(random(100) > 20){
                this_object()->eventMove(ob);
                detonate();
                return 0;
            }
        }
        else if(ob->GetMass() > 1000){
            if(random(100) > 30){
                detonate();
                return 0;
            }
        }
    }
    return ::eventNegotiateObstacles();
}

mixed eventEncounterBlock(){
    detonate();
    return ::eventEncounterBlock();
}

void analyze(string str){
    string tmp,tmp2;
    sscanf(str,"%s#%s",tmp,tmp2);
    if(tmp="/lib/corpse"){
        filter(deep_inventory(find_object(str)), (: $1->eventDestruct() :), this_object() );
    }
    return;
}

int HitLivings(object ob){
    int dam = GetDamage();
    ob->eventReceiveDamage("plasma bolt", HEAT, dam);
    return 1;
}

int SetArmed(int x){
    if(x) armed = 1;
    else armed = 0;
    if(armed) set_heart_beat(1);
    return armed;
}

int eventCruise(string str){
    return ::eventCruise(str);
}

int eventDestruct(){
    return ::eventDestruct();
}
