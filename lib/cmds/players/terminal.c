/*    /cmds/player/terminal.c
 *    from the Foundation II LPC Library
 *    allows a person to set their terminal manually
 *    created by Descartes of Borg 950501
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !args || args == "" ) return "设置成什么？";
    message("system", "终端已设置为 " +
            this_player()->SetTerminal(args) + "。", this_player());
    return 1;
}

string GetHelp() {
    return ("用法: terminal <终端类型>\n\n"
            "如果MUD没有自动识别正确的设置，"
            "你可以手动设置终端类型。\n"
            "参考: screen, env");
}
