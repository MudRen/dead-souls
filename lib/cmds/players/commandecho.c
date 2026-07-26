#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string *clrs = ({ "red", "green", "yellow", "blue",
            "cyan", "magenta", "black", "white" });
    if( !sizeof(str) )
        return "用法: commandecho <on 或 off 或 颜色>";
    str = lower_case(str);

    if( str != "on" && str != "off" && member_array(str, clrs) == -1 )
        return "用法: help commandecho";
    this_player()->SetProperty("commandecho", ( str == "off" ? 0 : str ));
    message("system",
            "你的命令回显已设置为 "+str+"。",
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: commandecho <on | off | 颜色>\n\n"
            "启用或禁用输入命令后的最后一行显示。"
            "仅当你启用了 reprompt 和/或 charmode 时才有用。"
            "你可以指定颜色，使用以下任意一种："
            "red, green, yellow, blue, cyan, magenta, black, "
            "white。例如：\ncommandecho blue\n"
            "参考: reprompt, charmode");
}

