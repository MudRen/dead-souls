#include <lib.h>

inherit LIB_DAEMON;

int cmd(string arg){
    if(!archp(previous_object())) return 0;
    cache_stats();
    return 1;
}

string GetHelp(){
    return "语法：cache\n\n"
        "从驱动获取缓存统计信息，包括命中率。"
        "\n参见 man: cache_stats"
        "\n另见：callouts, mstatus, netstat, opcprof, fdinfo, dumpallobj";
}
