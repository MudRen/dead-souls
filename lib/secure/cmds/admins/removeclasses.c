#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    foreach(string str in CLASSES_D->GetClasses()){
        CLASSES_D->RemoveClass(str);
    }
    write("完成。");
    return 1;
}

string GetHelp(){
    return ("语法: removeclasses\n\n"
            "移除职业守护进程中所有已知的职业。"
            "除非你想以后非常后悔，否则你应该"
            "立即使用 addclasses 命令重新添加职业。");
}
