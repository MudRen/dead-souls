#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    int what;
    if( !sizeof(str) )
        return "用法: chancolors <on 或 off>";
    str = lower_case(str);
    if( str != "on" && str != "off" )
        return "你只能将 chancolors 设置为 'on' 或 'off'";
    if(str == "on") what = 0;
    else what = 1;
    this_player()->SetNoChanColors(what);
    message("system",
            "彩色频道模式已"+str+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: chancolors [on | off]\n\n"
            "此命令允许你切换是否在频道消息中看到颜色。\n注意: 这不适用于频道名称的正常颜色。");
}

