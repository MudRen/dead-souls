/*    From the Dead Souls Object Library
 *    Provides follow/trail support for mobile objects.
 *    Works closely with LIB_LEAD.
 *    Created by Rush 951028
 */

#include <lib.h>
#include "include/follow.h"

private nosave object Leader;

protected void create(){ Leader = 0; }

mixed direct_follow_liv(){
    if( this_object() == this_player() )
        return "那样行不通。";
    return this_player()->CanFollow(this_object());
}

object SetLeader(object leader){
    if( leader == this_object() ) return 0;
    if( leader && Leader ) return 0;
    Leader = ( leader && leader->GetFollowers() ) ? leader : 0;
    return Leader;
}

object GetLeader(){ return Leader; }

varargs mixed CanFollow(object ob){
    if( ob ){
        if( !ob->CanLead() )
            return "你无权跟随" + ob->GetName();
        if( IsFollowing(ob) )
            return "你已经在跟随" + ob->GetName() + "了";
        if( ob->IsFollowing(this_object()) )
            return ob->GetName() + "已经在跟随你了。";
        if( ob == this_object() )
            return "你不可能那样做。";
    }
    return 1;
}

int IsFollowing(object ob){
    if( !Leader ) return 0;
    if( Leader == ob ) return 1;
    if( Leader->IsFollowing(ob) ) return 1;
    return 0;
}

/*
 * eventFollow() needs to be overriden by child classes to provide the
 * actual move support.
 */
int eventFollow(object dest, int fC){ return 0; }


