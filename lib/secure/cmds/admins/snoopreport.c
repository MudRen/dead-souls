#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string ret;

    if(!this_player() || !archp(this_player())) return 0;

    ret = SNOOP_D->Report();

    if(check_string_length(ret) > 0) this_player()->eventPrint(""+ret+"");
    else print_long_string(this_player(),ret);

    return 1;
}

string GetHelp() {
    return ("语法: snoopreport\n\n"
            "显示谁在监听谁、谁正在被监控（即记录）等信息。\n"
            "另见: snoop, unsnoop, monitor");
}
