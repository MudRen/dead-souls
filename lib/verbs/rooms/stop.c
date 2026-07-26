/*    /verbs/rooms/stop.c
 *    from the Dead Souls Mud Library
 *    stop STR
 *    created by Descartes of Borg 951016
 */

#include <lib.h>
#include "include/stop.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("stop");
    SetRules("STR");
}

mixed can_stop_str(string str){ 
    return this_player()->CanStop(this_player(), str);
}

mixed do_stop_str(string str){
    return this_player()->eventStop(this_player(), str);
}

string GetHelp(){
    return ("用法：stop [ fishing | fighting ]\n\n"
            "终止指定的活动。\n"
            "另见：fish, attack");
}
