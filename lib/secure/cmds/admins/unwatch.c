#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string which, nom;

    if(!archp(previous_object())) return 0;
    if(!str) {
        notify_fail("要取消监控哪个名称或站点？\n");
        return 0;
    }
    if(sscanf(str, "%s %s", which, nom) != 2) {
        notify_fail("正确语法: unwatch [name|site] [IP或名称]\n");
        return 0;
    }
    if(which == "name") BANISH_D->unwatch_name(nom);
    else if(which == "site") BANISH_D->unwatch_site(nom);
    else {
        notify_fail("未定义的取消监控类型: "+str+"\n");
        return 0;
    }
    message("info", nom+" 已取消"+which+"监控", this_player());
    return 1;
}

string GetHelp(){
    return ("语法: unwatch <[site|name] | "
            "[要取消监控的IP或站点]>\n\n"
            "取消监控特定名称的玩家或来自特定站点的玩家登录时的记录。\n"
            "示例: unwatch name forlock    unwatch site 134.181.*\n"
            "另见: watch, whowatched");
}
