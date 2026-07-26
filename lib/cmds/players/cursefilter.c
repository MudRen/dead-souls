#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    int status;
    if(!sizeof(str)) return "用法: help cursefilter";
    status = this_player()->GetParanoia("cursefilter");
    if(str == "on" && status) return "它已经开启了！";
    if(str == "off" && !status) return "它已经关闭了！";
    if(str == "on"){
        this_player()->SetParanoia("cursefilter", 1);
        write("脏话过滤器已启用。");
        return 1;
    }
    if(str == "off"){
        this_player()->SetParanoia("cursefilter", 0);
        write("脏话过滤器已禁用。");
        return 1;
    }
    return "输入: help cursefilter";
}

string GetHelp() {
    return ("用法: cursefilter [ on | off ]\n\n"
            "如果启用，会尝试屏蔽一些常见的不礼貌用语。\n"
            "参考: env");
}
