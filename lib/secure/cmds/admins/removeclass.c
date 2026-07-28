/*    /secure/cmds/admins/removeclass.c
 *    from the NIghtmare V Object Library
 *    removes classes
 *    created by Descartes of Borg 960528
 *    Version: %I%
 *    Last Modified: %D%
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !args || args == "" ) return "语法: removeclass <职业名>";
    CLASSES_D->RemoveClass(args);
    previous_object()->eventPrint("职业已移除。");
    return 1;
}

string GetHelp(){
    return ("语法: removeclass <职业名>\n\n"
            "从游戏中移除一个职业。\n"
            "另见: addclass, addemote, addrace, removerace");
}
