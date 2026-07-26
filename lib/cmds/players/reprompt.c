#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !sizeof(str) )
        return "用法: reprompt <on 或 off>";
    str = lower_case(str);
    if( str != "on" && str != "off" )
        return "你只能将 reprompt 设置为 'on' 或 'off'";
    this_player()->SetProperty("reprompt", ( str == "on" ? 1 : 0 ));
    message("system",
            "重提示模式已"+str+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: reprompt [on | off]\n\n"
            "启用或禁用接收消息后重新绘制提示符。并非所有客户端都支持此功能。"
            "注意，除非同时启用了 charmode，否则未完成的命令可能会显示异常。\n"
            "参考: charmode, prompt, env");
}

