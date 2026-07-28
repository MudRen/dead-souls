#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    foreach(string str in RACES_D->GetRaces()){
        RACES_D->RemoveRace(str);
    }
    write("完成。");
    return 1;
}

string GetHelp(){
    return ("语法: removeraces\n\n"
            "移除种族守护进程中所有已知的种族。"
            "除非你想以后非常后悔，否则你应该"
            "立即使用 addraces 命令重新添加种族。");
}
