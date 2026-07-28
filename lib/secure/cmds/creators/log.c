//      /bin/dev/_log.c
//      from the Dead Souls Mudlib
//      tails a given log
//      created by Brian@TMI 920128

#include <lib.h>
#include <dirs.h>

inherit LIB_DAEMON;

int cmd(string str) {
    if(!str) {
        notify_fail("正确语法: <log [日志文件]>\n");
        return 0;
    }
    write(str+":\n");
    if(!tail(DIR_LOGS+"/"+str)) write("没有该日志文件: "+str+"\n");
    return 1;
}

string GetHelp(){
    return ("语法: log [日志文件]\n\n"
            "查看指定的日志文件（即 mud 日志目录中的文件）。\n"
            "另见:\nelog, replog\n");
}
