/*    /lib/position.c
 *    From the Dead Souls Mud Library
 *    Handles the positioning of living things
 *    Created by Descartes of Borg 961221
 *    Version: @(#) position.c 1.1@(#)
 *    Last modified: 96/12/21
 */

#include <position.h>
#include <medium.h>
#include <message_class.h>
#include <daemons.h>

inherit LIB_FALL;
inherit LIB_SINK;

private int           Position = POSITION_STANDING;
private nosave object Chair    = 0;

// abstract methods
varargs mixed eventPrint(string str, mixed args...);
// end abstract methods

int GetPosition(){
    return Position;
}

int SetPosition(int x){
    Position = x;
}

varargs mixed eventLay(object target){
    mixed tmp;

    if( Position != POSITION_STANDING && Position != POSITION_SITTING){
        eventPrint("你必须站立或坐着才能躺下。");
        return 1;
    }
    if( !target ){
        send_messages("lie", "$agent_name $agent_verb down.", this_object(),
                0, environment());
        Position = POSITION_LYING;
        return 1;
    }
    tmp = target->eventReceiveLay(this_object());
    if( tmp != 1 ){
        if( !tmp ){
            eventPrint("你不能躺在那里！");
        }
        else {
            eventPrint(tmp);
        }
        return 1;
    }
    send_messages("lie", "$agent_name $agent_verb down on " +
            target->GetShort() + ".", this_object(), 0, environment());
    Position = POSITION_LYING;
    Chair = target;
    return 1;

}

varargs mixed eventKneel(object target){
    mixed tmp;

    if( Position != POSITION_STANDING && Position != POSITION_SITTING){
        eventPrint("你必须站立或坐着才能跪下。");
        return 1;
    }
    if( !target ){
        send_messages("kneel", "$agent_name $agent_verb down.", this_object(),
                0, environment());
        Position = POSITION_KNEELING;
        return 1;
    }
    return 1;
}

varargs mixed eventSit(object target){

    if( Position != POSITION_STANDING && Position != POSITION_LYING ){
        eventPrint("你无法从当前姿势坐下。");
        return 1;
    }
    if( !target ){
        if( Position == POSITION_STANDING){
            send_messages("sit", "$agent_name $agent_verb down.", 
                    this_object(),0, environment());
        }
        else send_messages("sit", "$agent_name $agent_verb up.",
                this_object(),0, environment());

        Position = POSITION_SITTING;
        return 1;
    }
    tmp = target->eventReceiveSit(this_object());
    if( tmp != 1 ){
        if( !tmp ){
            eventPrint("你不能坐在那里！");
        }
        else {
            eventPrint(tmp);
        }
        return 1;
    }
    send_messages("sit", "$agent_name $agent_verb down on " +
            target->GetShort() + ".", this_object(), 0, environment());
    Position = POSITION_SITTING;
    Chair = target;
    return 1;
}

mixed eventFly(){
    if( Chair ){
        mixed tmp = Chair->eventReleaseStand(this_object());

        if( tmp != 1 ){
            if( !tmp ){
                eventPrint("你无法站起来！");
            }
            else {
                eventPrint(tmp);
            }
            return 1;
        }
        Chair = 0;
    }
    if(this_object()->CanFly() && Position != POSITION_FLYING){
        tell_object(this_object(),"你开始飞行。");
        say(this_object()->GetName()+"开始飞行，悬浮在空中。");
        Position = POSITION_FLYING;
    }
    return 1;
}

mixed eventSwim(){
    if( Chair ){
        mixed tmp = Chair->eventReleaseStand(this_object());

        if( tmp != 1 ){
            if( !tmp ){
                eventPrint("你做不到！");
            }
            else {
                eventPrint(tmp);
            }
            return 1;
        }
        Chair = 0;
    }
    if(this_object()->CanSwim() && Position != POSITION_SWIMMING){
        tell_object(this_object(),"你开始游泳。");
        say(this_object()->GetName()+"开始游泳。");
        Position = POSITION_SWIMMING;
    }
    return 1;
}

mixed eventFloat(){
    if( Chair ){
        mixed tmp = Chair->eventReleaseStand(this_object());

        if( tmp != 1 ){
            if( !tmp ){
                eventPrint("你做不到！");
            }
            else {
                eventPrint(tmp);
            }
            return 1;
        }
        Chair = 0;
    }
    if(this_object()->CanFloat() && Position != POSITION_FLOATING){
        tell_object(this_object(),"你开始漂浮。");
        say(this_object()->GetName()+"开始漂浮。");
        Position = POSITION_FLOATING;
    }
    return 1;
}

mixed eventLand(){
    object env = environment();
    if(!env) return 0;
    if(! Position == POSITION_FLYING ) return 0;
    if( env->GetMedium() == MEDIUM_AIR || env->GetMedium() == MEDIUM_WATER ||
            env->GetMedium() == MEDIUM_SPACE ) return 0;  
    write("你停止了飞行。");
    say(this_object()->GetName()+"停止了飞行。");
    if(stringp(hobbled(this_object()))) Position = POSITION_STANDING;
    else Position = POSITION_LYING;
    return 1;
}

mixed eventStand(){
    if(!stringp(hobbled(this_object()))){
        eventPrint("你的伤势使你无法站立。");
        return 1;
    }
    if(RACES_D->GetLimblessRace(this_object()->GetRace()) ){
        eventPrint("你没有可以站立的四肢。");
        return 1;
    }
    if( Position == POSITION_STANDING ){
        eventPrint("你已经站着了！");
        return 1;
    }
    if( Position == POSITION_FLYING){
        return eventLand();
    }

    if( Chair ){
        mixed tmp = Chair->eventReleaseStand(this_object());

        if( tmp != 1 ){
            if( !tmp ){
                eventPrint("你无法站起来！");
            }
            else {
                eventPrint(tmp);
            }
            return 1;
        }
        Chair = 0;
    }
    Position = POSITION_STANDING;
    send_messages("stand", "$agent_name $agent_verb up.", this_object(), 0,
            environment());
    return 1;
}

object GetFurniture(){
    if(Chair) return Chair;
}
string GetFurnitureName(){
    if(Chair) return Chair->GetShort();
    else return "none";
}
