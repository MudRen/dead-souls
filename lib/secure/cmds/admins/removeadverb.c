/*    /secure/cmds/admins/removeadverb.c
 *    From the Dead Souls Mud Library
 *    Command for removing adverbs from the soul
 *    Created by Descartes of Borg 961214
 *    Version: @(#) removeadverb.c 1.1@(#)
 *    Last modified: 96/12/14
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !args || args == "" ) {
        return "要移除哪个副词？";
    }
    if( !SOUL_D->RemoveAdverb(args) ) {
        previous_object()->eventPrint("副词移除失败。");
        return 1;
    }
    previous_object()->eventPrint("副词已移除。");
    return 1;
}

string GetHelp(){
    return ("语法: removeadverb <副词>\n\n"
            "允许你从系统副词列表中移除一个副词，"
            "这些副词可以在大多数灵魂命令中使用。\n"
            "另见: addadverb, addemote, removeemote");
}
