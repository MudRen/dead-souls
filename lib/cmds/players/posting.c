//  Command _posting.c
//  Written by Hanse@Dead Souls 6/21/93

#include <lib.h>
inherit LIB_DAEMON;

int cmd(string str) {
    object *list;
    int i;

    if(str) return 0;
    list=users();
    write("\n正在使用编辑器的用户列表：\n");
    for(i=0;i<sizeof(list);i++)
        if(!list[i]->GetInvis() && list[i]->GetKeyName())
            if(present("mailer", list[i]))
                printf("%s - 在邮件编辑器中。\n",
                        arrange_string( list[i]->GetName(), 20));
            else if(in_edit(list[i]) || in_input(list[i]))
                printf("%s - 编辑中。\n",
                        arrange_string( list[i]->GetName(), 20));
    return 1;
}

string GetHelp() {
    return "用法: posting\n\n"
        "显示用户是否在编辑器中、在公告板上发帖或在邮件编辑器中。";
}
