/*    /verbs/players/stand.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960711
 *    Version: @(#) stand.c 1.5@(#)
 *    Last Modified: 96/12/21
 */

#include <lib.h>
#include <daemons.h>
#include <position.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("stand");
    SetRules("", "up");
    SetErrorMessage("站起来？");
    SetSynonyms("get up");
    SetHelp("用法：stand [up]\n"
            "当坐着或躺着时，你可以用这种方式站起来。\n"
            "另见：lie, sit");
}

mixed can_stand_up() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了。";
    }
    if(RACES_D->GetLimblessRace(this_player()->GetRace()) ){
        return "你没有可以站立的肢体。";
    }

    if(!environment(this_player())->CanStand(this_player())){
        return "你不能在这里站立。";
    }

    if( this_player()->GetPosition() != POSITION_STANDING ) {
        return 1;
    }
    return "你已经站着了！";
}

mixed can_stand(){
    return can_stand_up();
}

mixed do_stand_up() {
    return this_player()->eventStand();
}

mixed do_stand() {
    return this_player()->eventStand();
}
