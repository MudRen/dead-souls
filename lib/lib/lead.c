/*    From the Dead Souls Object Library
 *    Provides lead support for mobile objects.
 *    Works closely with LIB_FOLLOW.
 *    Created by Rush 951028
 */

#include <lib.h>
#include <position.h>
#include "include/lead.h"

private nosave mapping Followers;
private nosave int numberOfFollowers;

protected void create(){
    Followers = ([]);
    numberOfFollowers = 0;
}

mixed direct_lead_liv(){
    if( this_object() == this_player() ) return "那太蠢了。";
    return this_player()->CanLead();
}

mixed direct_evade_liv(){
    if( this_object() == this_player() ) return "那太蠢了。";
    return this_player()->CanEvade(this_object());
}

object *AddFollower(object follower){
    mapping tmp = ([]);

    if( !objectp(follower) ) error("Bad argument 1 to AddFollower().\n");
    if( follower != this_object() && !Followers[follower]
            && !follower->GetProperty("no follow") ){
        if( !follower->IsFollowing(this_object()) ){
            if( follower->SetLeader(this_object()) ){
                tmp["followed"] = 0;
                tmp["bonus"] = 0;
                tmp["lost"] = 0;
                Followers[follower] = tmp;
                numberOfFollowers++;
            }
        }
    }
    return GetFollowers();
}

object *RemoveFollower(object follower){
    if( !objectp(follower) ) error("Bad argument 1 to RemoveFollower().\n");
    map_delete(Followers, follower);
    follower->SetLeader(0);
    numberOfFollowers = sizeof(GetFollowers());
    return GetFollowers();
}

object *GetFollowers(){ return filter(keys(Followers), (: $1 :)); }

mapping GetFollowerMap(){ return copy(Followers); }

int SetFollowed(object follower, int followed){
    if( !objectp(follower) ) error("Bad argument 1 to SetFollowed().\n");
    if( !intp(followed) ) error("Bad argument 2 to SetFollowed().\n");
    if( !Followers[follower] ) return 0;
    return(Followers[follower]["followed"] = followed);
}

int GetFollowed(object follower){
    if( !objectp(follower) ) error("Bad argument 1 to GetFollowBonus().\n");
    if( !Followers[follower] ) return 0;
    return Followers[follower]["followed"];
}

int AddFollowBonus(object follower, int bonus){
    if( !objectp(follower) ) error("Bad argument 1 to AddFollowBonus().\n");
    if( !intp(bonus) ) error("Bad argument 2 to AddFollowBonus().\n");
    if( !Followers[follower] ) return 0;
    return( Followers[follower]["bonus"] += bonus );
}

int GetFollowBonus(object follower){
    if( !objectp(follower) ) error("Bad argument 1 to GetFollowBonus().\n");
    if( !Followers[follower] ) return 0;
    return Followers[follower]["bonus"];
}

varargs mixed CanLead(object ob){
    if( ob ){
        if( !ob->CanFollow() )
            return "你没有权力领导" + ob->GetName();
        if( ob->IsFollowing(this_object()) )
            return "你已经在领导" + ob->GetName() + "了";
        if( this_object()->IsFollowing(ob) )
            return ob->GetName() + "已经在领导你了。";
        if( ob == this_object() )
            return "你不可能那样做。";
    }
    return 1;
}

varargs mixed CanEvade(object ob){
    if( ob && !ob->IsFollowing(this_object()) )
        return ob->GetName() + "没有在跟随你。";
    return 1;
}

int eventMoveFollowers(object dest){
    mapping follower;
    object ob;
    int followChance;
    int badpos;

    badpos = (POSITION_NULL|POSITION_SITTING|POSITION_LYING|POSITION_KNEELING);

    foreach(ob in GetFollowers()){
        int pos = ob->GetPosition();
        follower = Followers[ob];
        if(ob->GetSleeping() || ob->GetParalyzed() || pos & badpos
                || this_object()->GetInvis() ){
            eventEvade(ob);
            RemoveFollower(ob);
            continue;
        }
        followChance = 100;
        if( !follower["followed"] ) followChance -= 20 + this_object()->GetSkillLevel("stealth");
        followChance += ob->GetSkillLevel("tracking");
        followChance += follower["bonus"];
        if( ob->eventFollow(dest, followChance) ) follower["lost"] = 0;
        else if( follower["lost"]++ && eventEvade(ob) ){
            RemoveFollower(ob);
        }
    }
    return 1;
}

int eventEvade(object ob){
    mixed ret;
    ret = CanEvade(ob);
    if( stringp(ret) ) error(ret);
    if( ret = 1 ){
        ob->eventPrint(this_object()->GetName() + "甩掉了你。");	this_object()->eventPrint("你甩掉了" + ob->GetName() + "。");
        return 1;
    }
    return 0;
}
