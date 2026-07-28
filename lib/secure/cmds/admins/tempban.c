// _tempban.c
// /cmd// Part of the Dead Souls Mudlib
// A command so that all those law-types can place sites on registration for a 
// specified, limited amount of time.
// 01July1994 by Gregon@Dead Souls

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string site;
    int time;

    if(!archp(previous_object())) return 0;

    if(!str) {
        write("以下站点正在临时注册中:\n"+
                BANISH_D->query_temp_site_info());
        return 1;
    }


    if(sscanf(str, "%s %d", site, time) != 2) {
        notify_fail("正确语法: tempban [站点] [分钟数]>\n\n");
        return 0;
    }

    write(site+" 现已临时注册 "+time+" 分钟。");
    BANISH_D->temporary_register(site, time*60);
    log_file("watch/register", site+" for "+time+" minutes.\n");
    log_file("watch/register", "by " +this_player()->GetName()+"\n");
    return 1;
}

string GetHelp(){
    return ("语法: tempban [站点] [时间]\n\n"
            "使来自指定站点的新玩家在指定时间内（以分钟为单位）"
            "无法登录。此设置在重启后仍然有效，站点IP地址"
            "的输入方式与 register 命令相同。"
            "详见 \"help register\"。\n\n"
            "注意: 不带参数的 tempban 将列出所有临时注册的站点"
            "及其过期时间。");
}
