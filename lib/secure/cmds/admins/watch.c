#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string which, nom;

    if(!archp(previous_object())) return 0;
    if(!str) {
        notify_fail("要监控哪个名称或站点？\n");
        return 1;
    }
    if(sscanf(str, "%s %s", which, nom) != 2) {
        notify_fail("正确语法: watch [name|site] [IP或名称]\n");
        return 1;
    }
    if(which == "name") BANISH_D->watch_name(nom);
    else if(which == "site") BANISH_D->watch_site(nom);
    else {
        notify_fail("未定义的监控类型: "+str+"\n");
        return 1;
    }
    message("info", nom+" 现已设为"+which+"监控", this_player());
    return 1;
}

string GetHelp(){
    return ("语法: watch <[site|name] | [要监控的IP或站点]>\n\n"
            "设置监控，当特定名称的玩家或来自特定站点的玩家登录时会被记录。"
            "示例: watch name forlock    watch site 134.181.*\n"
            "另见: unwatch, whowatched");
}
