#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    if(!(this_player()->GetInCombat())){
        write("你不在战斗中。");
        return 1;
    }
    this_player()->eventWimpy("go out");
    return 1;
}

string GetHelp() {
    return ("语法：flee\n\n"
            "如果你需要匆忙离开战斗，不在乎往哪个方向逃。\n"
            "此命令对创建者无效。");
}
