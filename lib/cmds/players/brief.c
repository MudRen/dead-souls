/*  /cmds/player/brief.c
 *  A command which allows players to toggle brief room descriptions
 *  Created by Blitz at NM-IVD
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !sizeof(str) )
        return "用法: brief <on 或 off>";
    str = lower_case(str);
    if( str != "on" && str != "off" )
        return "你只能将简要模式设置为 'on' 或 'off'";
    this_player()->SetBriefMode(str == "on");
    message("system",
            "简要模式已"+(str == "on" ? "开启" : "关闭")+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("Syntax: brief [on | off]\n\n"
            "This command allows you to toggle brief room descriptions "
            "on or off.\nSee also: env");
}

