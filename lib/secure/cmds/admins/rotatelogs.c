#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string arg) {
    int ret;
    int force = 0;
    if(arg) force = 1;
    ret = LOG_D->RotateLogs(force);
    if(ret){
        write("日志已轮转。");
    }
    else {
        write("日志轮转失败。");
    }
    return 1;
}

string GetHelp(){
    return ("语法: rotatelogs <force>\n\n"
            "如果旧日志文件过大则进行归档。带参数时，"
            "无论大小都会执行归档。");
}
