#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!sizeof(this_player()->GetMuffed())) return "你没有屏蔽任何人。";
    else if(!str || str == "") return "请更具体一些。";
    else {
        string *iglist = this_player()->GetMuffed();
        if(member_array(lower_case(str),iglist) == -1) return "你没有屏蔽他们。";
        iglist -= ({ lower_case(str) });
        this_player()->SetMuffed(iglist);
        write("你已将 "+capitalize(str)+" 从屏蔽列表中移除。");
    }
    return 1;
}

string GetHelp() {
    return ("用法: unmuff <名称>\n\n"
            "此命令允许你停止屏蔽指定名称的频道消息。\n"
            "参考: earmuff, whomuffed");
}

