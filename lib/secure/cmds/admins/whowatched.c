#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *who;

    if(!str) {
        notify_fail("查看站点还是名称？\n");
        return 0;
    }
    if(!archp(previous_object())) return 0;
    if(str == "name") who = BANISH_D->query_watched_names();
    else if(str == "site") who = BANISH_D->query_watched_sites();
    else {
        notify_fail("查看什么类型的监控？\n");
        return 0;
    }
    message("info", sprintf("以下%s正在被监控:", str),this_player());
    this_player()->more(explode(format_page(who, 5), "\n"));
    return 1;
}

string GetHelp(){
    return ("语法: whowatched name\n"
            "        whowatched site\n\n"
            "列出被监控的站点或名称。");
}
