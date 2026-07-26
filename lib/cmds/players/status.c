/*    /cmds/player/status.c
 *    from the Dead Souls LPC Library
 *    gives a player status information
 *    created by Descartes of Borg 950409
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) { return this_player()->eventDisplayStatus(); }

string GetHelp() {
    return ("用法: status\n\n"
            "显示你当前的物理状态信息。\n"
            "参考: money, skills, stats, score, env");
}
