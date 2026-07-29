#include <lib.h>
#include <medium.h>
#include <daemons.h>
#include <position.h>
#include <armor_types.h>
#include <message_class.h>
#include <vision.h>
#include "include/npc.h"

private int Mount;

object *Riders = ({});

mixed direct_ride_str(){
    return this_object()->GetMount();
}

mixed direct_ride_word_str(){
    return this_object()->GetMount();
}

mixed direct_mount_liv(){
    return this_object()->GetMount();
}

mixed direct_dismount_liv(){
    return this_object()->GetMount();
}

mixed direct_dismount_from_liv(){
    return this_object()->GetMount();
}

int eventRide(string direction){
    string travel_cmd, s1, s2;
    if(interactive(this_object())) return 0;
    if(sscanf(direction,"%s %s",s1,s2) == 2){
        if(s1 == "enter" || s1 == "into") travel_cmd = "enter";
    }

    if(!s1 || s1 == "") switch(this_object()->GetPosition()){
        case POSITION_STANDING : travel_cmd = "go";break;
        case POSITION_SITTING : travel_cmd = "crawl";break;
        case POSITION_LYING : travel_cmd = "crawl";break;
        case POSITION_FLYING : travel_cmd = "fly";break;
        default : travel_cmd = "go";
    }
    else direction = s2;
    this_object()->eventForce(travel_cmd+" "+direction);
    return 1;
}

object *AddRider(object ob){
    Riders += ({ ob });
}

object *RemoveRider(object ob){
    Riders -= ({ ob });
}

object *GetRiders(){
    object *ret = ({});
    if(Riders && sizeof(Riders)){
        foreach(mixed rider in Riders){
            if(!rider) RemoveRider(rider);
            else if(environment(rider) == this_object()) ret += ({ rider });
            else RemoveRider(rider);
        }
    }
    return ret;
}

int SetMount(int x){
    Mount = x;
    if(Mount) this_object()->SetNoClean(1);
    return Mount;
}
int GetMount(){ return Mount; }

varargs mixed eventMount(object who, int quiet, int forced){
    int rider_weight;
    string weight = "weight";
    if(!who){
        return 0;
    }
    if(environment() && environment()->GetMedium() == MEDIUM_SPACE){
        weight = "mass";
    }
    rider_weight = who->GetMass();
    if(!environment(this_object())){
        return 0;
    }
    if(environment(who) && environment(who) == this_object()){
        if(!forced && !quiet){
            return who->eventPrint("你已经骑上了。", MSG_ERROR);
        }
    }
    if((rider_weight + this_object()->GetCarriedMass()) > 
            this_object()->GetMaxCarry()){
        if(!forced && !quiet){
            return write(this_object()->GetShort()+
                    "无法承受那么多"+weight+"。");
        }
    }
    if(this_object()->GetMountOwner() != who){
        if(!forced && !quiet){
            write(this_object()->GetName()+"和你不够熟悉，"
                    "不允许你骑"+objective(this_object())+"。");
            return 0;
        }
    }
    this_object()->SetNoClean(1);
    if(!quiet){
        write("你骑上了"+this_object()->GetShort()+"。");
        say(who->GetName()+"骑上了"+this_object()->GetShort()+"。");
    }
    who->SetProperty("mount", this_object());
    if(who->eventMove(this_object())) return AddRider(who);
    if(forced) return AddRider(who);
    else return 0;
}

varargs mixed eventDismount(object who, int quiet, int forced){
    int rider_weight;
    rider_weight = who->GetMass();
    if(!environment(this_object())) return 0;
    if(environment(who) && environment(who) != this_object()){
        if(!forced || !quiet){
            return who->eventPrint("你已经下马了。", MSG_ERROR);
        }
    }
    else {
        if(!quiet){
            write("你从"+this_object()->GetPlainShort()+"上下来了。");
            tell_room(environment(this_object()),who->GetName()+"从" +this_object()->GetPlainShort()+"上下来了。", ({ this_object(), who }));
        }
        who->RemoveProperty("mount");
        if(who->eventMove(environment(this_object()))) return RemoveRider(who);
        else return 0;
    }
}

mixed eventBuck(object who){
    int rider_weight;
    rider_weight = (who->GetCarriedMass()) + (who->GetMass() || 2000);
    if(!environment(this_object())) return 0;
    if(environment(who) && environment(who) != this_object()){
        return 0;
    }
    else {
        tell_player(who,"你被从"+
                (this_object()->GetPlainShort() || this_object()->GetShort())+"上甩了下来！");
        tell_room(environment(this_object()),who->GetName()+
                "被从"+(this_object()->GetPlainShort() ||
                    this_object()->GetShort())+"上甩了下来！", ({ this_object(), who }));
        who->RemoveProperty("mount");
        who->SetPosition(POSITION_LYING);
        if(who->eventMove(environment(this_object()))) return RemoveRider(who);
        else return 0;
    }
}
