/*    /verbs/rooms/go.c
 *    from the Dead Souls Mud Library
 *    go STR
 *    go into STR
 *    created by Descartes of Borg 951104
 */

#include <lib.h>
#include "include/go.h"

inherit LIB_VERB;

protected void create(){
    verb::create();
    SetVerb("go");
    SetRules("STR", "into STR");
    SetErrorMessage("往哪个方向走？");
    SetHelp("用法：go <方向>\n"
            "      go into <地点>\n\n"
            "让你朝指定方向移动，或进入指定地点。\"go into\" 命令与 \"enter\" 命令同义。"
            "注意，大多数方向已经为你预设了别名。例如，\"go south\" 已被预设为 \"s\"。\n"
            "另见：climb, enter, jump, fly, swim");
}

mixed can_go_str(string str){
    if( !environment(this_player()) ) return "你不在任何地方。";
    if( this_player()->GetStaminaPoints() <3 )
        return "你现在太累了，哪也去不了。";
    if(!stringp(hobbled(this_player()))) return "你的伤势阻碍了你的行动。也许你应该试试爬行。";
    return environment(this_player())->CanGo(this_player(), str);
}

mixed can_go_into_str(string str){
    if( !environment(this_player()) ) return "你不在任何地方。";
    if( this_player()->GetStaminaPoints() <3 )
        return "你现在太累了。";
    if(!stringp(hobbled(this_player()))) return "你的伤势阻碍了你的行动。也许你应该试试爬行。";
    return environment(this_player())->CanEnter(this_player(), str);
}

mixed do_go_str(string str){
    return environment(this_player())->eventGo(this_player(), str);
}

mixed do_go_into_str(string str){
    return environment(this_player())->eventEnter(this_player(), str);
}
