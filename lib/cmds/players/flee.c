#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!(this_player()->GetInCombat())){
        write("你没有在战斗中。");
        return 1;
    }
    this_player()->eventWimpy("go out");
    return 1;
}

string GetHelp() {
    return ("用法: flee\n\n"
            "如果你需要紧急脱离战斗，且不在乎往哪个方向逃跑。\n"
            "此命令对创造者无效。");
}
