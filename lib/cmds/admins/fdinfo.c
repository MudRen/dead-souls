#include <lib.h>

inherit LIB_DAEMON;

int cmd(string arg){
    if(!archp(previous_object())) return 0;
    write(dump_file_descriptors());
    return 1;
}

string GetHelp(){
    return "语法：fdinfo\n\n"
        "列出机器文件描述符的状态。"
        "\n参见 man: dump_file_descriptors"
        "\n另见：netstat, mstatus, cache, callouts, dumpallobj, opcprof";
}
