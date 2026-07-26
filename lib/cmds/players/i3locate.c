/*    /cmds/players/i3locate.c
 *    from the Dead Souls LPC Library
 *    Intermud 3 command to locate people on other MUDs
 *    created by Descartes of Borg 950624
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !args || args == "" ) return "i3locate 谁？";
    SERVICES_D->eventSendLocateRequest(convert_name(args));
    message("system", "i3locate 查询已发送。", this_player());
    return 1;
}

string GetHelp() {
    return ("用法: i3locate [人物]\n\n"
            "此命令允许你了解通过 Intermud 3 网络连接的哪些MUD上"
            "有人使用你指定的名称。请注意，此人可能实际上不是"
            "你认为的那个人，因为没有机制阻止不同的人在不同的MUD上使用相同的名称。\n"
            "参考: mail, mudlist, rwho, tell");
}
