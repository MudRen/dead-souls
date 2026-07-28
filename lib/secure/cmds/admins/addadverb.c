/*    /secure/cmds/admins/addadverb.c
 *    From the Dead Souls Mud Library
 *    Command for adding new adverbs to the soul
 *    Created by Descartes of Borg 961214
 *    Version: @(#) addadverb.c 1.1@(#)
 *    Last modified: 96/12/14
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string* adverbs;

    if( !args || args == "" ) {
        return "要添加哪个副词？";
    }
    adverbs = map(explode(args, ","), (: trim :));
    if( !SOUL_D->AddAdverbs(adverbs...) ) {
        previous_object()->eventPrint("副词添加失败。");
        return 1;
    }
    previous_object()->eventPrint("副词已添加。");
    return 1;
}

string GetHelp(string args) {
    return ("语法: addadverb 副词1,..,副词n\n\n"
            "允许你添加一个或多个用逗号分隔的副词到系统副词列表中，"
            "这些副词可以在大多数灵魂命令中使用。\n"
            "另见: addemote,removeadverb,removeemote");
}
