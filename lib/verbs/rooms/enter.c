/*    /verbs/rooms/enter.c
 *    from the Dead Souls Mud Library
 *    created by Descartes of Borg 951104
 *    Version: @(#) enter.c 1.2@(#)
 *    Last modified: 96/10/15
 */

#include <lib.h>
#include "include/enter.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("enter");
    SetRules("into OBJ", "OBJ");
    SetErrorMessage("进入什么？");
    SetHelp("用法：enter <地点>\n"
            "      enter into <地点>\n\n"
            "让你进入指定的地点。\"go\" 命令用于朝某物移动，而 \"enter\" 命令用于进入某物内部。\n"
            "另见：go");
}

mixed can_enter_obj(){
    if( this_player()->GetParalyzed() ){
        return "你什么也做不了。";
    }
    if(!stringp(hobbled(this_player()))) return "你的伤势阻碍了你的行动。也许你应该试试爬行。";
    return 1;
}

mixed can_enter_into_obj(){
    return can_enter_obj();
}

mixed do_enter_obj(object targ, string what){
    return targ->eventEnter(this_player(), remove_article(lower_case(what)));
}

mixed do_enter_into_obj(object targ, string what) {
    do_enter_obj(targ, what);
}
