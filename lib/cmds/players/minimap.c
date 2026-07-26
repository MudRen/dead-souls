#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
#if MINIMAP
    int status = this_player()->GetProperty("minimapping");
    string sstatus = "正在";
    if(!status) sstatus = "没有";
    if(!args){
        write("你"+sstatus+"显示小地图。");
        return 1;
    }
    if(args == "on"){
        if(status) write("你已经在显示小地图了。");
        else write("你启用了小地图。");
        this_player()->SetProperty("minimapping", 1);
        return 1;
    }

    if(args == "off"){
        if(!status) write("你已经没有显示小地图了。");
        else write("你禁用了小地图。");
        this_player()->SetProperty("minimapping", 0);
        return 1;
    }

    write("用法: help minimap");
    return 1;
#else
    write("此功能已禁用。");
    return 1;
#endif
}

string GetHelp() {
    return ("用法: minimap [on | off]\n\n"
            "如果启用，当向你描述环境时会显示一个简单的周围地图。\n"
            "参考: env, terminal, brief, mute, gag.");
}
