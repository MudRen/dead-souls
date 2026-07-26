/*    /cmds/player/converse.c
 *    from the Dead Souls LPC Library
 *    allows a person to talk without having to use the say command
 *    created by Descartes of Borg 950419
 */

#include <lib.h>
#include <talk_type.h>
#include <commands.h>

inherit LIB_DAEMON;

protected void eventChat(string args);

mixed cmd(string args) {
    message("system", "进入对话模式。继续输入你想"
            "说的话，直到完成。", this_player());
    message("system", "完成后，在一行中单独输入 '.' 就像在编辑器中一样。",
            this_player());
    message("system", "______________________________________________________"
            , this_player());
    input_to( (: eventChat :));
    return 1;
}

protected void eventChat(string args) {
    if( trim(args) == "." ) {
        message("system", "退出对话模式。", this_player());
        return;
    }
    else this_player()->eventSpeak(0, TALK_LOCAL, args);
    input_to( (: eventChat :) );
}

string GetHelp() {
    return ("用法: converse\n\n"
            "进入对话模式，你输入的任何内容都会像在前面加上了"
            "\"say\"命令一样。进入对话模式后，"
            "你可以像退出邮件或公告板编辑器一样退出，"
            "即在一行中单独输入 '.'。"
            "你也可以在对话模式下通过在输入前加 ! 来执行命令。\n"
            "参考: say, tell");
}
