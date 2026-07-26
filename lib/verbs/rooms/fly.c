/*    /verbs/rooms/fly.c
 *    from the Dead Souls Mud Library
 *    Like go, except for flying around
 *    created by Descartes of Borg 961013
 *    Version: @(#) fly.c 1.2@(#)
 *    Last modified: 96/10/13
 */

#include <lib.h>
#include <medium.h>
#include <daemons.h>
#include <position.h>
#include "include/fly.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("fly");
    SetRules("", "STR", "into STR");
    SetErrorMessage("往哪个方向飞？");
    SetHelp("用法：fly [方向]\n"
            "      fly into <地点>\n\n"
            "让你朝指定方向飞行，或飞进指定地点。\"fly into\" 命令与 \"enter\" 命令同义。\n"
            "另见：climb, enter, go, jump, swim");
}

int StaminaCost(){
    int cost = 15;
    int bonus = this_player()->GetStatLevel("durability")/10;
    bonus += this_player()->GetStatLevel("coordination")/20;
    bonus += this_player()->GetFood()/40;
    bonus += this_player()->GetDrink()/40;
    cost -= bonus;
    if(cost < 1) cost = 1;
    return cost;
}

mixed can_fly(){
    object env = environment(this_player());
    if( !env ){
        return "你根本不在任何地方！";
    }
    if(this_player()->GetPosition() == POSITION_FLYING)
        return "你已经在飞了。";
    if(env->CanFly(this_player())) return this_player()->CanFly();
    return "你不能在这里飞。";
}

mixed can_fly_str(string str){
    object env = environment(this_player());
    int envpos = env->GetPosition();
    if( !env ){
        return "你不在任何地方。";
    }
    if( this_player()->GetStaminaPoints() < 15 ){
        return "你现在太累了，哪也飞不了。";
    }
    if(env->CanFly(this_player(), str)){
        if(envpos == POSITION_FLYING) return 1;
        return this_player()->CanFly();
    }
    if(this_player()->GetPosition() != POSITION_FLYING &&
            envpos != POSITION_FLYING){
        return "你没有在飞。";
    }
    return 0;
}

mixed can_fly_into_str(string str){
    object env = environment(this_player());
    int envpos = env->GetPosition();
    if( !env ){
        return "你不在任何地方。";
    }
    if( this_player()->GetStaminaPoints() < 3 )
        return "你现在太累了。";
    if(environment(this_player())->CanEnter(this_player(), str)){
        if(envpos == POSITION_FLYING) return 1;
        return this_player()->CanFly();
    }
    if(this_player()->GetPosition() != POSITION_FLYING &&
            envpos != POSITION_FLYING){
        return "你没有在飞。";
    }
    else return 0;
}

mixed do_fly(){
    return this_player()->eventFly();
}

mixed do_fly_str(string str){
    this_player()->AddStaminaPoints(-StaminaCost());
    return environment(this_player())->eventGo(this_player(), str);
}

mixed do_fly_into_str(string str){
    this_player()->AddStaminaPoints(-StaminaCost());
    return environment(this_player())->eventEnter(this_player(), str);
}
