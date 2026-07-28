#include <lib.h>
#include <dirs.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string arg){
    int ret;
    object whom;
    if(!archp(previous_object())) return 0;
    if(!arg || arg == "me") arg = this_player()->GetKeyName();
    if(!(whom = find_player(arg))){
        write("未找到该用户。");
        return 1;
    }
    whom->CancelCharmode();
    ret = RELOAD_D->ReloadPlayer(arg, 1);
    if(!ret) write("发生错误。");
    else write("完成。");
    whom = find_player(arg);
    if(whom) whom->CancelCharmode();
    return 1;
}

string GetHelp(){
    return "语法: userload <用户名>\n\n"
        "重新加载用户代码，为指定用户创建新身体，并将他们切换到新身体中。"
        "此命令用于在不退出的情况下测试用户对象中的新功能。\n"
        "另见: reload, update, warmboot ";
}
