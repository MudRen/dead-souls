#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string res;
    string *sites;

    if(!archp(previous_object())) return 0;
    if(res=catch(sites = call_other(BANISH_D, "query_registered"))) {
        write("检查站点时出错："+res+"\n");
        return 1;
    }
    sites = sort_array(sites, "order_sites", this_object());
    if(str) {
        if(member_array(str, sites) == -1)
            write("站点 \""+str+"\" 当前不在注册列表中。\n");
        else write("站点 \""+str+"\" 当前在注册列表中。\n");
    }
    else {
        write("来自这些站点的人当前必须注册才能创建角色：\n");
        this_player()->more(explode(format_page(sites, 5), "\n"));
    }
    return 1;
}

int order_sites(string alpha, string beta) {
    string *a, *b;
    int i, x, y;

    a = explode(alpha, ".");
    b = explode(beta, ".");
    for(i=0; i<sizeof(a) && i<sizeof(b); i++) {
        if(!(x = to_int(a[i]))) return -1;
        if(!(y = to_int(b[i]))) return 1;
        if(x > y) return 1;
        if(y > x) return -1;
    }
    if(sizeof(a) < sizeof(b)) return -1;
    else return (sizeof(a) > sizeof(b));
}

string GetHelp(){
    return ("语法：whoregistered [站点]\n\n"
            "不带参数时，列出所有需要注册才能在MUD上创建角色的站点。"
            "指定站点参数时，确认该站点是否需要注册。"
            "站点必须使用IP数字格式。\n另见："
            "register, unregister, banish, unbanish, whobanished, "
            "watch, unwatch, whowatched");
}
