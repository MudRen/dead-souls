#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
#ifndef __GET_CHAR_IS_BUFFERED__
    write("此游戏不支持此模式。请让你的mud管理员考虑使用 GET_CHAR_IS_BUFFERED 重新编译。");
    return 1;
#endif
    if( !sizeof(str) )
        return "用法: charmode <on 或 off>";
    str = lower_case(str);

    if( str != "on" && str != "off" )
        return "你只能将 charmode 设置为 'on' 或 'off'";
    if(str == "on") this_player()->SetCharmode(1);
    else this_player()->CancelCharmode();
    this_player()->SetProperty("reprompt", this_player()->GetCharmode());
    message("system",
            "你的字符模式已"+str+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: charmode [on | off]\n\n"
            "启用或禁用终端的'字符模式'。"
            "除非你使用非常基本的mud客户端（如Linux telnet命令），"
            "否则不应启用此功能，因为大多数mud客户端更喜欢使用行模式，"
            "如果启用字符模式会出问题。\n"
            "参考: reprompt, prompt, env");
}

