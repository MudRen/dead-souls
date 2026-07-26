/*  /cmds/player/date.c
 *  A simple command which displays current date and time
 *  Blitz@NM-IVD
 */

#include <lib.h>
#include <daemons.h>
#include <localtime.h>

mixed cmd(string timezone) {
    string *parts, year, time, tz;
    int offset, x, hour, min, sec;

    if(!timezone || !valid_timezone(timezone)){
        timezone = this_player()->GetProperty("timezone");
    }
    if(!timezone || !valid_timezone(timezone)) timezone = local_time()[9];

    offset = TIME_D->GetOffset(timezone);
    offset += EXTRA_TIME_OFFSET;
    if(query_os_type() != "windows" ) 
        x = offset * 3600;
    else x = 0;
    time = ctime( time() + x );
    x = sizeof(parts = explode(time, " "));
    year = parts[x - 1];
    sscanf(parts[x - 2], "%d:%d:%d", hour, min, sec);
    message("info",
            sprintf("时间: %d:%s%d %s\n日期: %s, %s",
                (hour>12 ? (hour-12) : (hour == 0 ? 12 : hour)),
                (min < 10 ? "0" : ""),
                min,
                ((hour>11 && hour) ? "下午" : "上午"),
                implode(parts[0..(x-3)], " "),
                year),
            this_player() );
    return 1;
}

string GetHelp() {
    return ("用法: date\n\n"
            "显示本地时间的当前时间和日期。");
}
