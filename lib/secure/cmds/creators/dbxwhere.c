/* Beek - 10/4/94 */
#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    mapping error;
    object ob;
    int i;

    if (str) {
        ob = find_player(str);
        if (!ob) {
            return "玩家未找到。";
        }
    } else
        ob = this_player();
    if (error = ob->GetLastError()) {
        return sprintf("%s\n", master()->standard_trace(error, 1));
    } else write("没有错误。\n");
    return "dbxwhere运行完成。";
}

string GetHelp(){
    return "Syntax: dbxwhere [person]\n\n"
        "Debugging thingy.\nSee also: dbxframe";
}
