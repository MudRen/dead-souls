#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    object ob;

    if(!archp(previous_object())) {
        write("只有管理员才能停止监控进程。");
        return 0;
    }
    if( !str || str == "" ) {
        write("要取消监控谁？\n");
    }
    else if(!user_exists(str))
        write(str+": 没有这个玩家。\n");
    else{
        SNOOP_D->RemoveMonitor(this_player(), str);
        write("监听守护进程已收到你的请求。");
    }
    return 1;
}

string GetHelp(){
    return "语法: unmonitor <用户名>\n\n"
        "停止记录用户的输入和输出。\n"
        "另见: monitor, snoop, unsnoop";
}
