/*    /secure/cmds/admins/removerace.c
 *    from the NIghtmare V Object Library
 *    removes races
 *    created by Descartes of Borg 960528
 *    Version: %I%
 *    Last Modified: %D%
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if( !args || args == "" ) return "语法: removerace <种族名>";
    RACES_D->RemoveRace(args);
    previous_object()->eventPrint("种族已移除。");
    return 1;
}

string GetHelp(string str) {
    return ("语法: removerace <种族名>\n\n"
            "从游戏中移除一个种族。\n"
            "另见: addclass, addemote, addrace, removeclass");
}
