#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
#if (WIZMAP && GRID)
    int status = this_player()->GetProperty("wizmapping");
    string sstatus = "正";
    if(!status) sstatus = "没有";
    if(!args){
        write("你"+sstatus+"在使用巫师地图。");
        return 1;
    }
    if(args == "on"){
        if(status) write("你已经在使用巫师地图了。");
        else write("你启用了巫师地图。");
        this_player()->SetProperty("wizmapping", 1);
        return 1;
    }

    if(args == "off"){
        if(!status) write("你已经不在使用巫师地图了。");
        else write("你禁用了巫师地图。");
        this_player()->SetProperty("wizmapping", 0);
        return 1;
    }

    write("试试: help wizmap");
    return 1;
#else
    write("此功能已禁用。");
    return 1;
#endif
}

string GetHelp() {
    return ("Syntax: wizmap [on | off]\n\n"
            "If enabled, a simple map of your surroundings is displayed "
            "when your environment is described to you.\nSee also: "
            "env, terminal, brief, mute, gag, minimap.");
}
