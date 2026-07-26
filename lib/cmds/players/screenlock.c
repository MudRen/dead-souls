#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !sizeof(str) )
        return "用法: screenlock <on 或 off>";
    str = lower_case(str);
    if( str != "on" && str != "off" )
        return "你只能将 screenlock 设置为 'on' 或 'off'";
    this_player()->SetProperty("screenlock", (str == "on"));
    message("system",
            "屏幕锁定模式已"+str+"。",
            this_player() );
    return 1;
}

string GetHelp(){
    return ("用法: screenlock [on | off]\n\n"
            "此命令允许你切换是否允许客户端在初始登录协商后"
            "自动更改屏幕大小设置。\n"
            "参考: screen, terminal, env");
}
