//      /bin/adm/_removeguest.c
//      from the Dead Souls Mudlib
//      removes a person from the guest list for when the mud is locked
//      created by Descartes of Borg 08 july 1993

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *guests;
    int i;

    if(!archp(previous_object())) return 0;
    if(!str) {
        notify_fail("正确语法: removeguest [访客列表]\n");
        return 0;
    }
    i = sizeof(guests = explode(str, " "));
    while(i--) BANISH_D->remove_guest(guests[i]);
    message("info", "访客已移除。", this_player());
    return 1;
}

string GetHelp(){
    return ("语法: removeguest [玩家列表]\n\n"
            "从MUD锁定期间允许登录的访客列表中移除一个或多个玩家。"
            "此功能通常用于撤销通过 addguest 命令授予的访问权限。\n"
            "另见: addguest, whoguests");
}
