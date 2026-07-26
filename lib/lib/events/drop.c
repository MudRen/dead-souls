/*    /lib/drop.c
 *    From the Dead Souls Mud Library
 *    Makes an object something which can be dropped
 *    Created by Descartes of Borg 960113
 *    Version: @(#) drop.c 1.2@(#)
 *    Last modified: 96/12/22
 */

#include <lib.h>
#include <function.h>
#include ROOMS_H

private mixed PreventDrop = 0;
private mixed DestructOnDrop = 0;

// abstract methods
string GetDefiniteShort();
mixed eventMove(mixed dest);
// end abstract methods

mixed GetPreventDrop(){
    return PreventDrop;
}

mixed SetPreventDrop(mixed val){
    if(!intp(val) && !stringp(val) && !functionp(val) && !objectp(val) ){
        error("Bad argument 1 to SetPreventDrop().\n");
    }
    return (PreventDrop = val);
}

int GetDestructOnDrop(){
    return DestructOnDrop;
}

int SetDestructOnDrop(int val){
    return (DestructOnDrop = val);
}

mixed CanDrop(object who){
    if( !PreventDrop ){
        return 1;
    }
    if( intp(PreventDrop) ){
        return 0;
    }
    if( stringp(PreventDrop) ){
        return PreventDrop;
    }
    if( objectp(PreventDrop) ){
        if( PreventDrop == who ){
            return capitalize(GetDefiniteShort()) +
                " 根本不想离开你的手中。";
        }
        else {
            return 1;
        }
    }
    else {
        if( functionp(PreventDrop) & FP_OWNER_DESTED ){
            return "函数对象出现问题。";
        }
        return evaluate(PreventDrop, who);
    }
}

mixed eventDrop(object who){
    mixed tmp;

    if( who != environment() ){
        return 0;
    }

    if(DestructOnDrop) tmp = eventMove(ROOM_FURNACE);
    else tmp = eventMove(environment(who));

    if( !tmp ){
        who->eventPrint("有什么东西阻止你放下 "
                + GetDefiniteShort() + "。");
        return 1;
    }
    if( tmp != 1 ){
        return tmp;
    }
    send_messages("drop", "$agent_name 丢弃了 $target_name。",
            who, this_object(), environment(who));
    if(DestructOnDrop) tell_room(environment(who),capitalize(this_object()->GetShort())+" 在一道闪光中消失了！");
    return 1;
}

mixed direct_drop_obj(object target){
    if( environment() != this_player() ){
        return "#你没有那样东西可以丢弃。";
    }
    return CanDrop(this_player());
}
