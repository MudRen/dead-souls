/*    /cmd *    from the Dead Souls Mudlib
 *    Shows when the next reboot occurs
 *    created by Descartes of Borg 940130
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string form) {
    string str, tz;
    int x, offset;

    if(DISABLE_REBOOTS){
        write("定期重启已禁用。");
        write("事件守护进程没有安排重启。");
        return 1;
    }
    tz = this_player()->GetProperty("timezone");
    if(!tz || !valid_timezone(tz)) tz = query_tz();

    offset = TIME_D->GetOffset(tz);
    offset += EXTRA_TIME_OFFSET;

    x = EVENTS_D->GetRebootInterval() * 3600;
    x = (time() - uptime()) + x;
    if(query_os_type() != "windows" )
        x += offset * 3600;
    str = tz+ " " + ctime(x);
    message("system", "当前 "+tz+" 系统时间是 "+timestamp(tz),
            this_player());
    if(form && form == "string") return "下次重启将在 " + str + "。";
    else message("system", "下次重启将在 " + str + "。",this_player());
    return 1;
}

string GetHelp(){
    return ("用法: nextreboot\n\n"
            "告诉你 " + mud_name() + " 下次定期重启的时间。");
}
