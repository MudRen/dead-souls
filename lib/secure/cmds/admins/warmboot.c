#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string arg){
    if(!archp(previous_object())) return 0;
    RELOAD_D->WarmBoot();
    write("已请求热重启。");
    return 1;
}

string GetHelp(){
    return "语法: warmboot\n\n"
        "重新加载并更新内存中的对象和用户，使代码更改生效，"
        "如同MUD已重启。此命令不会断开玩家连接。"
        "警告: 正在编辑文件的人会丢失未保存的更改。\n"
        "另见: reload, update, userload ";
}
