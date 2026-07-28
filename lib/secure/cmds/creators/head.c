/*    /secure/ambassador/_head.c
 *    from Dead Souls 3.3
 *    gives the first 22 lines of a file
 *    created by Descartes of Borg 940928
 */

#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *lines;
    string file;
    int x;

    if(!str) return notify_fail("语法: head <文件>\n");
    file = absolute_path(this_player()->query_cwd(),str);
    if(!file_exists(file)) return notify_fail("没有该文件: "+file+"\n");
    else if(!(str = read_file(file)))
        return notify_fail("空文件: "+file+"\n");
    if((x = sizeof(lines = explode(str, "\n"))) > 22) x = 23;
    str = implode(lines[0..x-1], "\n");
    message("system", str, this_player());
    return 1;
}

string GetHelp() {
    return ("语法: head <文件>\n\n"
            "显示指定文件的开头若干行。\n"
            "另见: cat, more, tail");
}
