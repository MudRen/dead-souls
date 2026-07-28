//      /bin/adm/_whobanished.c
//      from the Dead Souls Mudlib
//      lists all names banished from usage
//      originally written by Shadowwolf@Dead Souls 
//      rewritten for the new Dead Souls security system by Descartes of Borg
//      930809

#include <lib.h>
#include <daemons.h>

int cmd(string str) {
    string *noms;

    if(!archp(previous_object())) return 0;
    noms = BANISH_D->query_banished();
    if(str) {
        if(member_array(lower_case(str), noms) == -1) 
            write(str+" 当前不是被封禁的名称。\n");
        else write(str+" 是一个被封禁的名称。\n");
    }
    else {
        write("以下名称当前被封禁:\n");
        this_player()->more(explode(format_page(noms, 4), "\n"));
    }
    return 1;
}

string GetHelp(){
    return ("语法: whobanished [名称]\n\n"
            "不带参数时，此命令列出当前所有被封禁的名称。"
            "否则将确认该名称是否被封禁。");
}
