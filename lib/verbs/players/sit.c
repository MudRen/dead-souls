/*    /verbs/players/sit.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 960711
 *    Version: @(#) sit.c 1.7@(#)
 *    Last Modified: 96/12/21
 */

#include <lib.h>
#include <position.h>
#include <rounds.h>

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("sit");
    SetRules("", "up","down", "down in OBJ", "down on OBJ", "in OBJ", "on OBJ");
    SetErrorMessage("坐下？");
    SetHelp("用法：sit [down]\n"
            "      sit down in <物品>\n\n"
            "允许你坐在地上或椅子类物品上。\n"
            "另见：lie, stand");
}

mixed can_sit_down() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了！";
    }
    if(!environment(this_player())->CanSit(this_player())){
        return "你不能在这里坐下。";
    }
    if( this_player()->GetPosition() == POSITION_SITTING ) {
        return "你已经坐着了！";
    }
    if( this_player()->GetPosition() != POSITION_STANDING ) {
        return "你必须站着才能坐下！";
    }
    return 1;
}

mixed can_sit_up() {
    if( this_player()->GetParalyzed() ) {
        return "你什么也做不了！";
    }
    if( this_player()->GetPosition() != POSITION_LYING ) {
        return "你必须躺着才能坐起来！";
    }
    return 1;
}

mixed can_sit(){
    if(this_player()->GetPosition() == POSITION_LYING) return can_sit_up();
    else return can_sit_down();
}

mixed can_sit_word_obj() {
    return can_sit_down();
}

mixed can_sit_down_word_obj() {
    return can_sit_down();
}

mixed do_sit(){
    return this_player()->eventSit();
}

mixed do_sit_down() {
    return this_player()->eventSit();
}

mixed do_sit_up() {
    return this_player()->eventSit();
}


mixed do_sit_word_obj(string word, object target) {
    return this_player()->eventSit(target);
}

mixed do_sit_down_word_obj(string word, object target) {
    return this_player()->eventSit(target);
}
