//      /bin/adm/_addguest.c
//      from the Dead Souls Mudlib
//      adds a person to the guest list for when the mud is locked
//      created by Descartes of Borg 08 july 1993

#include <lib.h>
#include <privs.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *guests;
    mixed res;
    int i;

    if(!master()->valid_apply(({ PRIV_SECURE, PRIV_ASSIST }))){
        error("Illegal attempt to add a guest.");
    }

    if(!str) {
        notify_fail("正确语法: addguest [访客列表]\n");
        return 0;
    }
    i = sizeof(guests = explode(str, " "));
    while(i--) {
        if(!guests[i] || guests[i] == "") continue;
        if(res = catch(call_other(BANISH_D, "add_guest", guests[i]))) 
            message("admin", sprintf("添加访客 %s 时出错: %s",
                        guests[i], res), this_player());
    }
    message("admin", "访客已添加。", this_player());
    return 1;
}

string GetHelp() {
    return ("语法: addguest [玩家列表]\n\n"
            "将一个或多个玩家添加到MUD锁定期间允许登录的访客数据库中。"
            "通常用于允许不在 LOCKED_ACCESS_ALLOWED 定义的任何组中的"
            "人员进入，或允许单个玩家测试者登录。\n"
            "另见: removeguests, whoguests");
}
