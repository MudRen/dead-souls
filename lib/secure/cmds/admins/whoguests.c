//      /bin/adm/_whoguests.c
//      from the Dead Souls Mudlib
//      shows the list of guests allowed in when the mud is locked
//      created by Descartes of Borg 08 july 1993

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *guests;

    if(!archp(previous_object())) return 0;
    if(str) {
        notify_fail("正确语法: whoguests\n");
        return 0;
    }
    catch(guests = BANISH_D->query_guests());
    message("info", "以下人员在MUD锁定时被允许进入: ", this_player());
    if(!sizeof(guests)) message("info", "没有允许的访客。", this_player());
    else this_player()->more(explode(format_page(guests, 5), "\n"));
    return 1;
}

string GetHelp(){
    return ("语法: whoguests\n\n"
            "列出MUD锁定时被允许进入游戏的所有访客。\n"
            "另见: addguest, removeguest");
}
