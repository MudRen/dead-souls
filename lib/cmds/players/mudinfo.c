#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !sizeof(str) )
        return "用法: mudinfo <mud名称>";
    return MUDINFO_D->PrintMudInfo(str);
}

string GetHelp() {
    return ("用法: mudinfo <mud名称>\n\n"
            "如果可用，此命令显示指定mud的详细 Intermud-3 信息。");
}
