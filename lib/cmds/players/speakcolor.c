#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !sizeof(str) )
        return "用法: speakcolor <颜色>";
    this_player()->SetSpeakColor(str);
    write("%^BOLD%^"+this_player()->GetSpeakColor()+"这是你接收说话消息的当前颜色。");
    return 1;
}

string GetHelp() {
    return ("用法: speakcolor [ cyan | red | green | orange | yellow | blue | magenta | black | white ]\n"
            "        speakcolor [ b_cyan | b_red | b_green | b_orange | b_yellow | b_blue | b_magenta | b_black | b_white ]\n\n"
            "此命令允许你设置接收说话消息的颜色。");
}
