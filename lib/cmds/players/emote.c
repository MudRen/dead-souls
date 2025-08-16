/*    /cmds/player/emote.c
 *    from the Dead Souls LPC Library
 *    for those times when you are feeling emotional
 *    created by Descartes of Borg 950412
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !creatorp(this_player()) && !avatarp(this_player()) ) {
        if( this_player()->GetStaminaPoints() < 1 )
            return "你太累了。";
    }
    if( !args || args == "" ) {
        message("my_action", "你感觉充满情感。", this_player());
        message("other_action", this_player()->GetName() +
                " 看起来充满情感。", environment(this_player()),
                ({ this_player() }));
        return 1;
    }
    if( args[0] != '\'' ) args = " " + args;
    message("my_action", "你表达: " + this_player()->GetName() + 
            args, this_player());
    message("other_action", this_player()->GetName() + args,
            environment(this_player()), ({ this_player() }) );
    return 1;
}

string GetHelp() {
    return ("语法：emote <消息>\n\n"
            "将你指定的任何消息直接放在你的名字后面。例如，"
            "\"emote 微笑。\"会让其他人看到"
            "\"Descartes 微笑。\"。非管理员每次使用emote会失去一点体力值"
            "以防止滥用。");
}

