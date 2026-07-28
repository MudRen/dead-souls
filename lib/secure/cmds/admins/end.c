/*    /secure/cmds/adm/end.c
 *    from the Dead Souls LPC Library
 *    the command to reboot the MUD
 *    created by Descartes of Borg 950526
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    int x;

    if(!archp(previous_object())) return 0;
    if( !args || args == "" ) return "你必须指定延迟分钟数。";
    if( !(x = to_int(args)) ) return "你必须指定延迟分钟数。";
    if( x < 2 ) return "延迟时间至少为2分钟。";
    EVENTS_D->eventReboot(x);
    message("system", "重启序列已启动。", this_player());
    return 1;
}

string GetHelp() {
    return ("语法: end [延迟时间]\n\n"
            "启动重启序列，在指定的延迟时间后执行重启。"
            "延迟时间必须以分钟为单位，且至少为两分钟。\n"
            "另见: nextreboot, setreboot, shutdown");
}
