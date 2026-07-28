#include <lib.h>
#include <dirs.h>

inherit LIB_DAEMON;

int cmd(string arg)
{
    if(!archp(previous_object())) return 0;
    unguarded( (: opcprof("/log/opcprof.out") :) );
    write("请查看 /log/opcprof.out.efun 和 " +
            "/log/opcprof.out.eoper 以查看此命令的输出。");

    return 1;
}

string GetHelp(){
    return ("语法: opcprof\n\n"
            "将 efuns 和 eoperators 的列表输出到 /log/opcprof.out.*\n "
            "参见 man: opcprof\n"
            "另见: fdinfo, netstat, mstatus, cache, callouts, dumpallobj,");
}
