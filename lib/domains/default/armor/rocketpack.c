#include <lib.h>
#include <armor_types.h>
#include <damage_types.h>
#include <medium.h>
inherit LIB_ARMOR;
inherit LIB_ACTIVATE;
inherit LIB_READ;

int activated;
int charge = 1000;
int maxcharge = 1000;
object rocketshadow, owner;
string current_direction;
mapping Directions = ([]);

string LongD(){
    string ret = "这是一个穿戴在背部的大型装置，设计用于"推动"+
        "穿戴者在空中或太空中移动。要持续运作，"+
        "应该将其激活。燃料表显示"+
        "百分之"+to_int(percent(charge,maxcharge))+"。";
    return ret;
}

protected void create(){
    armor::create();
    if(!Directions) Directions = ([]);
    SetKeyName("rocket pack");
    SetId(({"pack","rocket"}));
    SetAdjectives(({"large","rocket"}));
    SetShort("一个小型火箭背包");
    SetLong( (: LongD :) );
    SetMass(800);
    SetBaseCost(18000);
    SetArmorType(A_VEST);
    AddSave( ({ "charge", "Directions" }) );
    SetRestrictLimbs( ({ "torso" }) );
    set_heart_beat(1);
}

void init(){
    ::init();
    add_action("boost","boost");
}

int SetCharge(int i){
    charge = i;
}

int SetMaxCharge(int i){
    maxcharge = i;
}

void heart_beat(){
    int medium;
    if(activated) charge--;
    if(charge < 1) charge = 0;
    if(!charge && activated){
        object env = environment();
        activated = 0;
        if(env){
            tell_object(env,"火箭背包发出噼啪声后熄灭了。");
        }
    }

    if(!owner) return;
    medium = environment(owner)->GetMedium();
    if(medium == MEDIUM_SPACE){
        int i;
        object env = environment(owner);
        if(!current_direction){
            current_direction = env->GetExits()[random(sizeof(env->GetExits()))];
        }
        if(activated){
            if(!Directions[current_direction]) Directions[current_direction] = 1;
            else Directions[current_direction]++;
        }
        foreach(mixed key, mixed val in Directions){
            if(val > 20) val = 20;
            for(i=val;i>0;i--){
                this_object()->boost(key,1);
            }
        }
    }
}

int boost(string str, int coasting){
    string dest,imsg,omsg;
    mapping Exit, Doors;
    int ret, medium;
    object env;
    if(!owner) return 0;
    env = environment(owner);
    current_direction = str;
    medium = environment(owner)->GetMedium();
    if(!env) return 0;
    Doors = env->GetDoorsMap();

    if(medium == MEDIUM_SPACE && !coasting){
        if(Directions[opposite_dir(str)]){
            Directions[opposite_dir(str)]--;
        }
        else {
            if(!Directions[str]) Directions[str] = 1;
            else Directions[str]++;
            //call_out( (: boost  :), 1, str, 1);
        }
    }

    if(!coasting && environment(this_object()) != owner){
        write("你没有火箭背包。");
        return 1;
    }
    if(!coasting && !GetWorn()){
        write("你没有穿戴火箭背包。");
        return 1;
    }
    if(!coasting && !str || !env){
        write("向哪个方向推进？");
        return 1;
    }

    if(!coasting && !charge){
        write("火箭背包没有燃料了。");
        return 1;
    }
    dest = env->GetExit(str);
    if(!dest){
        if(str == "up" && env->GetFlyRoom()) dest = env->GetFlyRoom();
        else if(str == "down" && env->GetSinkRoom()) dest = env->GetSinkRoom();
        else {
            if(!coasting) write("没有这个方向。");
            return 1;
        }
    }
    Exit = environment(owner)->GetExitData(str);

    if( sizeof(Doors) && Doors[str] && Doors[str]->GetClosed() ){
        message("my_action", "You bump into " +
                Doors[str]->GetShort(str) + ".", owner);
        return 1;
    }

    if( Exit && Exit["pre"] &&
            !(evaluate(Exit["pre"], str)) ){
        return 1;
        //return 1;
    }

    if(!sizeof(dest)){
        write("你不能往那个方向走。");
        return 1;
    }

    omsg = owner->GetName()+" rockets "+str+".";
    imsg = owner->GetName()+" rockets in.";

    if(!coasting) write("你启动了火箭背包的推进器，向"+str+"方向飞去。");
    if(!coasting) charge--;

    ret = owner->eventMoveLiving(dest, omsg, imsg, str);
    if(ret){
        if( Exit && Exit["post"] ) evaluate(Exit["post"], str);
        if(activated){
            if(!coasting) write("火箭背包的推进器恢复正常运转。");
        }
        else {
            if(!coasting) write("火箭背包的推进器发出噼啪声后熄灭了。");
        }
    }

    return 1;
}

int eventTurnOn(){
    if(!(this_object()->GetWorn()) || !this_player() ||
            environment(this_object()) != this_player()){
        write("你没有穿戴火箭背包。");
        return 1;
    }
    write("你激活了火箭背包，发出低沉的轰鸣声！");
    say(this_player()->GetName()+" fires up "+possessive(this_player())+" "
            "rocket pack with a deep, rumbling roar!");
    activated = 1;
    return 1;
}

int eventTurnOff(){
    write("你关闭了火箭背包。推进器发出噼啪声后熄灭了。");
    say(this_player()->GetName()+" deactivates "+possessive(this_player())+" "
            "rocket pack. The boosters sputter and go silent.");
    activated = 0;
    return 1;
}

int GetRunning(){
    return activated;
}

mixed eventEquip(object who, string* limbs){
    mixed success = armor::eventEquip(who, limbs);
    rocketshadow = new("/shadows/rocketpack");
    owner = who;
    if(success){
        if(rocketshadow) rocketshadow->eventShadow(who);
    }
    else if(rocketshadow) destruct(rocketshadow);
    activated = 0;
    return success;
}

varargs mixed eventUnequip(object who) {
    mixed success;
    if(!who) who = this_player();
    success = armor::eventUnequip(who);
    if(success){
        if(rocketshadow) rocketshadow->eventUnshadow();
    }
    if(rocketshadow) destruct(rocketshadow);
    return success;
}

int eventDecrementCharge(){
    if(!GetWorn()) return 0;
    if(previous_object() != rocketshadow) return 0;
    if(charge < 1) charge = 0;
    else charge--;

    if(charge < 50){
        tell_object(environment(this_object()),"火箭背包大声哔哔作响！");
        return charge;
    }

    if(charge < 100){
        tell_object(environment(this_object()),"火箭背包轻声哔哔作响。");
        return charge;
    }

    return charge;
}

int GetRemainingCharge(){
    return charge;
}

