#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string *cmds;
    if(!sizeof(args)){
        write("用法: help queue");
        return 1;
    }
    cmds = explode(args, ";");
    foreach(string cmnd in cmds){
        if(sizeof(cmnd)){
            write("排队命令: "+cmnd);
            this_player()->eventQueueCommand(cmnd);
        }
    }
    this_player()->eventExecuteQueuedCommands();
    return 1;
}

string GetHelp(){
    return ("用法: queue <命令1;命令2>\n\n"
            "将命令堆叠起来按顺序执行。");
}
