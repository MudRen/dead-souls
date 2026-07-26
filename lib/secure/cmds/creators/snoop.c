/*
// The snoop command.
// Daemonized by Buddha (2-19-92)
// Part of the TMI mudlib.
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    object ob;

    if( !str || str == "" ) {
        write("监听谁？\n");
    }
    else if(!(ob=find_player(str=lower_case(str))))
        write(str+": no such player.\n");
    else if(str == this_player()->GetKeyName()){
        write("那将是非常愚蠢的。");
        return 1;
    }
    else
        SNOOP_D->AddWatcher(this_player()->GetKeyName(), str);
    write("监听守护进程已收到你的请求。");
    return 1;
}

string GetHelp(){
    return "Syntax: snoop <user>\n\n"
        "Echoes to your screen everything <user> sees or types. "
        "To stop snooping, type just \"unsnoop <user>\"\n"
        "See also: unsnoop, monitor, unmonitor";
}
