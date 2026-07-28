//      /bin/adm/_broadcast.c
//      from the Dead Souls mudlib
//      like shout, except that it overrides ALL blocking
//      created by Descartes of Borg 930823

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!archp(previous_object())) return 0;
    if(!str) return "尝试：help broadcast";
    message("broadcast",
            sprintf("%%^RED%%^Broadcast message from %s: "
                "%%^YELLOW%%^%s%%^RESET%%^",
                this_player()->GetName(), str), users());
    return 1;
}

string GetHelp() {
    return "语法：broadcast [消息]\n\n"
        "发送一条不受任何形式屏蔽的消息。请勿用于叫喊比赛！";
}
