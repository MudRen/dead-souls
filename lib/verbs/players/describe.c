/*  Allows players to describe themselves.
 *  created by Rush@Dead Souls
 */

#include <lib.h>
#include "include/describe.h"

inherit LIB_VERB;

protected void create() {
    verb::create();
    SetVerb("describe");
    SetRules("LIV","STR");
    SetErrorMessage("用法：describe <消息>");
    SetHelp("用法：describe <消息>\n\n"
            "为玩家提供描述。你必须在描述中至少包含一个 $N 来表示你的名字。"
            "例如：如果我输入 'describe $N is nondescript.'，我的描述将是 'Rush is nondescript.'");
}

mixed can_describe_str(string str) {
    if(strsrch(str, "$N") == -1)
        return("你的描述必须至少包含一个 '$N' 来指定你的名字。");
    return 1;
}

mixed do_describe_str(string str) {
    this_player()->SetLong(str);
    write("好的。");
    return 1;
}
