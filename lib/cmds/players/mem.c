#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    int i, lines = 2 * this_player()->GetScreen()[1];
    write("行数: "+lines);
    for(i=lines;i>0;i--){
        write("正在加载内存测试...\n");
    }
    this_player()->eventPage(explode(mud_status(1), "\n"));
    return 1;

}

string GetHelp() {
    return ("用法: mem\n\n"
            "此命令让你看起来在做一些与内存相关的重要技术工作，"
            "但实际上它只是清除屏幕上的游戏文本。");
}
