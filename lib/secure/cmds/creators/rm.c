//      /bin/dev/_rm.c
//      from the Dead Souls Mudlib
//      the command to rm files (wild cards without prompt!!!!, be careful)
//      created by Descartes of Borg 02 august 1993

#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *files;
    string tmp;
    object ob;
    int i;

    if(!str) {
        notify_fail("正确语法: <rm [文件]>\n");
        return 0;
    }
    if((ob=previous_object())->GetForced()) {
        write("有人试图强迫你删除 "+str+"。");
        return 1;
    }
    tmp = absolute_path(ob->query_cwd(), str);
    if(!archp(ob) || !sizeof(files = wild_card(tmp)))
        files = ({ tmp });
    if(!(i=sizeof(files))) {
        message("system", "文件 "+tmp+" 不存在。", this_player());
        return 1;
    }
    while(i--) {
        switch(file_size(files[i])) {
            case -1: message("system", "文件 "+files[i]+" 不存在。",
                             this_player()); break;
            case -2: message("system", files[i]+" 是一个目录。",
                             this_player()); break;
            default: message("system", rm(files[i]) ? files[i]+": 完成。" :
                             files[i]+": 权限被拒绝。", this_player());
                     break;
        }
    }
    return 1;
}

string GetHelp(){
    string ret = "语法: rm [文件]\n\n"
        "此命令删除指定文件。一旦删除，文件无法恢复。真的无法恢复。";
    if(archp(this_player()))
        ret += "\n大管理员注意: 通配符可用于此命令，但没有确认提示，请非常小心！"; 
    return ret;
}
