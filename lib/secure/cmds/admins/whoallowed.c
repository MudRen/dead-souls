//      /bin/adm/_whoallowed.c
//      from the Dead Souls Mudlib
//      shows who can get in from registered sites
//      created by Shadowwolf@Dead Souls 93????
//      rewritten for the new security system by Descartes of Borg 930812

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *noms;

    if(!archp(previous_object())) return 0;
    if(!sizeof(noms = BANISH_D->query_allowed())) {
        write("当前没有人被允许从受限站点登录。\n");
        return 1;
    }
    if(str) {
        if(member_array(lower_case(str), noms) != -1)
            write("您已经允许 "+capitalize(str)+" 登录。\n");
        else write("该名称当前未设置为注册登录。\n");
    }
    else {
        write("以下名称可被来自受限站点的人使用：\n");
        write(format_page(noms, 5)+"\n");
    }
    return 1;
}

string GetHelp() {
    return ("语法：whoallowed [名称]\n\n"
            "列出可以被允许从需要注册角色才能游戏的站点进入游戏的玩家名称。");
}
