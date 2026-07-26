#include <lib.h>

inherit LIB_DAEMON;
string err =  "此游戏似乎未在驱动中启用此功能。请考虑让mud管理员重新编译，定义 PACKAGE_DSLIB。";


mixed cmd(string args) {
    mixed keepalive = this_player()->GetProperty("keepalive");
    if(!intp(keepalive)) keepalive = 0;

#ifndef __DSLIB__
    write(err);
    return 1;
#endif

    if( !args || args == "" ) {
        if(!keepalive){
            write("保活功能已禁用。");
            return 1;
        }
        else {
            write("保活设置为每 "+keepalive+" 次心跳发送一次。");
            return 1;
        }
    }
    if(!intp(keepalive = to_int(args)) || !keepalive) {
        this_player()->SetProperty("keepalive",0);
        write("保活功能已禁用。");
        return 1;
    }
    else {
        this_player()->SetProperty("keepalive",keepalive);
        write("保活设置为每 "+keepalive+" 次心跳发送一次。");
        return 1;
    }
}

string GetHelp(){
    return ("用法: keepalive [数字]\n\n"
            "不带参数时，keepalive 将显示当前的保活间隔。"
            "提供整数参数时，此命令设置向客户端发送不可见"
            "'保活'信号的频率。"
            "这对于那些ISP或调制解调器会断开空闲连接的用户很有用。"
#ifndef __DSLIB__
            "\n---注意---\n"+err+"\n---\n"
#endif
            "\n参考: env");
}
