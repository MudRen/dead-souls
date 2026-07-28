//      /bin/adm/_unregister.c
//      from the Dead Souls Mudlib
//      takes a site off of the list of sites needing to register
//      created by Shadowwolf@Dead Souls 93????
//      rewritten for the new 3.0 security system

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    if(!member_group(previous_object(), "SECURE")) {
        if(!member_group(previous_object(), "LAW")) return 0;
    }
    if(!str) return 0;
    if(member_array(str, BANISH_D->query_registered()) == -1) {
        write("该站点不在需要注册的站点列表中。\n");
        return 1;
    }
    BANISH_D->unregister_site(str);
    log_file("watch/register", previous_object()->GetKeyName()+
            " UNREGISTERED "+str+": "+ctime(time())+"\n");
    write("站点: "+str+" 已从注册列表中移除。\n");
    return 1;
}

string GetHelp() {
    return ("语法: unregister <站点>\n\n"
            "将站点从必须注册角色才能进入的列表中移除。\n"
            "另见: register, whoregistered, banish, unbanish, "
            "whobanished, letin, wholetin, unletin");
}
