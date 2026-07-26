#include <lib.h>
#include <vendor_types.h>
#include <damage_types.h>
inherit LIB_ITEM;
inherit LIB_PULL;
string pin_desc();
string lev_desc();
int detonated;
int count, armed;
string *limbs,domain;
void analyze(string butt);
int HitLivings(object munch);
int radius = 0;
object *whom;

void create(){
    item::create();
    SetKeyName("concussion hand grenade");
    sscanf(base_name(this_object()),"/domains/%s/%*s",domain);
    SetId( ({"grenade","hand grenade","flash-bang grenade","concussion grenade"}) );
    SetAdjectives( ({"military","pineapple"}) );
    SetShort("一枚手榴弹");
    SetLong("这是一枚 olive-green military issue hand grenade。它大约 the size of an apple， and its round exterior is made of smooth metal。 The grenade's fuse consists of a short metal lever and a round pull-pin。");
    SetMass(20);
    SetDollarCost(10);
    SetVendorType(VT_WEAPON);
    AddItem(({"pull pin","pull-pin","pin"}),"这是一个 round, metal pin， evidently designed for pulling。");
    AddItem(({"lever","metal lever"}),"这个 lever appears to be part of the fuse mechanism。");
    AddItem( ({"fuse","fuse mechanism"}) , "这个 fuse mechanism controls the arming of the grenade。");
    count=5;
    detonated=0;
}
void init(){
    if(armed){
        set_heart_beat(1);
        if(detonated==1) this_object()->eventDestruct();
    }
}

mixed CanPull(object who, string target) {
    if(!environment() || environment() != who ){
        return "#你没有手榴弹。";
    }
    if(answers_to(target,this_object())){
        return "#你不能拉那个。";
    }
    if(armed){
        return "#它已经 armed。";
    }
    if(!GetItem(target)){
        return "#那不在手榴弹上。";
    }
    return 1;
}

mixed eventPull(object who, string target) {
    string *tmpid;
    if(!environment() || (this_player() && environment() != this_player())){
        write("你没有 holding it。");
        return 1;
    }
    if(target =="pin" || target == "pull-pin"){
        tmpid = GetAdjectives();
        write("你拉开了手榴弹的 pin。\n");
        say(this_player()->GetName()+"从手榴弹上拉开了 pin。\n");
        new("/domains/"+domain+"/obj/pin")->eventMove(this_player());
        new("/domains/"+domain+"/obj/lever")->eventMove(this_player());
        SetShort("一枚 live 手榴弹");
        SetLong("这是一枚 olive-green military issue hand grenade。它大约 the size of an apple， and its round exterior is made of smooth metal。 The pin and spoon are missing from the fuse mechanism， indicating the grenade is live and will detonate very soon。");
        AddItem(({"lever","metal lever"}),"手榴弹已经 armed。 The fuse lever is no longer on the grenade。");
        AddItem(({"pull pin","pull-pin","pin"}),"手榴弹已经 armed。 There is no pin in the fuse。");
        armed = 1;
        set_heart_beat(1);
        SetAdjectives(tmpid + ({"armed","live","hissing"}));
        return 1;
    }
    write("什么都没发生。");
    return 1;
}
void heart_beat(){
    count--;
    if(detonated==1) this_object()->eventDestruct();
    if(count < 0){
        this_object()->detonate();
        return;
    }
    if(interactive(environment())){
        tell_object(environment(), "你 holding a live 手榴弹。");
        return;
    }
    tell_object(environment(),"你听到低沉的嘶嘶声。");
    tell_object(environment(environment()), environment()->GetName()+" holding a live 手榴弹。");
}
int detonate(){
    object ob;
    string *stuffs;
    int num;
    ob = environment(this_object());
    if(living(ob)){
        stuffs=ob->GetLimbs();
        tell_object(ob, "\nKABOOM！你被你的手榴弹 torn to pieces！\n");
        tell_room(environment(ob), "\nKABOOM！"+ob->GetName()+"被"+possessive(ob)+"手榴弹 torn to pieces！\n",ob);
        detonated=2;
        foreach(string limb in stuffs){
            if(limb != "head" && limb != "torso" && limb != "neck") ob->RemoveLimb(limb,this_object());
        }
        ob = environment(ob);
    }
    if(detonated !=2) tell_room(environment(this_object()), "\nKABOOM！手榴弹爆炸了！\n");
    if(!sizeof(get_livings(ob))) ob = environment(ob);
    if(ob && sizeof(whom = scramble_array(get_livings(ob)[0..12]))){
        tc("whom: "+identify(whom));
        foreach(object victim in whom){
            this_object()->HitLivings(victim);
        }
    }
    this_object()->eventDestruct();
    return 1;
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
    object env = environment();
    int dam;
    tc("victim: "+identify(ob));
    radius++;
    if(radius < 6) dam = random(1000)+500;
    else dam = (random(1000)+500) - (radius * 100);
    if(env && !living(env)){
        if(env->GetClimate() == "indoors") dam *= 2;
    }
    if(dam > 0){
        ob->eventReceiveDamage("concussion",OVERPRESSURE, dam, 0);
    }
    return 1;
}

int SetArmed(int x){
    if(x) armed = 1;
    else armed = 0;
    if(armed) set_heart_beat(1);
    return armed;
}
