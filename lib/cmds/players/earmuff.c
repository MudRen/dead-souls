#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!str || str =="") {
        if(!sizeof(this_player()->GetMuffed())) write("你没有屏蔽任何人。");
        else {
            write("你正在屏蔽以下名称：\n");
            write(implode(filter(this_player()->GetMuffed(), (: capitalize($1) :)), "\n")+"\n");
        }
        return 1;
    }
    else this_player()->AddMuffed(str);
    write("你已将 "+capitalize(str)+" 添加到屏蔽列表。");
    return 1;
}

string GetHelp() {
    return ("用法: earmuff\n"
            "        earmuff <名称>\n"
            "        earmuff @<mud>\n\n"
            "此命令允许你屏蔽来自指定名称的频道消息。\n"
            "你也可以屏蔽来自特定mud的所有频道消息，"
            "例如: earmuff @Spammy Mud II\n"
            "参考: whomuffed, unmuff");
}

