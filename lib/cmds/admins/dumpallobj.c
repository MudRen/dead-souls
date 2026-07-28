#include <lib.h>

inherit LIB_DAEMON;

int cmd(string arg){
    if(!archp(previous_object())) return 0;
    dumpallobj("/tmp/objects");
    return 1;
}

string GetHelp(){
    return "语法：dumpallobj\n\n"
        "将所有当前加载的对象列表输出到 /tmp/objects。"
        "\n参见 man: dumpallobj"
        "\n另见：callouts, cache, mstatus, netstat, fdinfo, opcprof";
}
