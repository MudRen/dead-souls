#include <lib.h>
#include <medium.h>
#include <daemons.h>
#include <position.h>
#include "include/swim.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("swim");
    SetRules("", "STR", "into STR");
    SetErrorMessage("往哪个方向游？");
    SetHelp("用法：swim <方向>\n"
            "      swim into <地点>\n\n"
            "让你朝指定方向游泳，或游进指定地点。\"swim into\" 命令与 \"enter\" 命令同义。\n"
            "另见：fly, climb, enter, go, jump");
}

int StaminaCost(){
    int cost = 20;
    int bonus = this_player()->GetStatLevel("durability")/10;
    bonus += this_player()->GetStatLevel("strength")/20;
    bonus += this_player()->GetFood()/40;
    bonus += this_player()->GetDrink()/40;
    cost -= bonus;
    if(cost < 1) cost = 1;
    return cost;
}

mixed can_swim(){
    object env = environment(this_player());
    if( !env ){
        return "你根本不在任何地方！";
    }
    if(this_player()->GetPosition() == POSITION_SWIMMING)
        return "你已经在游泳了。";
    if(!RACES_D->CanSwim(this_player()->GetRace())){
        return capitalize(pluralize(this_player()->GetRace()))+"不会游泳。";
    }
    if(env->CanSwim(this_player())) return this_player()->CanSwim();
    return "你不能在这里游泳。";
}

mixed can_swim_str(string str){
    object env = environment(this_player());
    int envpos = env->GetPosition();
    if( !env ){
        return "你不在任何地方。";
    }
    if( this_player()->GetStaminaPoints() < 15 ){
        return "你现在太累了，哪也游不了。";
    }
    if(env->CanSwim(this_player(), str)){
        if(envpos == POSITION_SWIMMING) return 1;
        return this_player()->CanSwim();
    }
    if(this_player()->GetPosition() != POSITION_SWIMMING &&
            envpos != POSITION_SWIMMING){
        return "你没有在游泳。";
    }
    return 0;
}

mixed can_swim_into_str(string str){
    object env = environment(this_player());
    int envpos = env->GetPosition();
    if( !env ){
        return "你不在任何地方。";
    }
    if( this_player()->GetStaminaPoints() < 3 )
        return "你现在太累了。";
    if(environment(this_player())->CanEnter(this_player(), str)){
        if(envpos == POSITION_SWIMMING) return 1;
        return this_player()->CanSwim();
    }
    if(this_player()->GetPosition() != POSITION_SWIMMING &&
            envpos != POSITION_SWIMMING){
        return "你没有在游泳。";
    }
    return 0;
}

mixed do_swim(){
    return this_player()->eventSwim();
}

mixed do_swim_str(string str){
    this_player()->AddStaminaPoints(-StaminaCost());
    return environment(this_player())->eventGo(this_player(), str);
}

mixed do_swim_into_str(string str){
    this_player()->AddStaminaPoints(-StaminaCost());
    return environment(this_player())->eventEnter(this_player(), str);
}
