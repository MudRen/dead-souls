/*    /secure/cmds/creator/tail.c
 *    from the Foundation II Object Library
 *    Displays the last screenful of information from a file
 *    created by Descartes of Borg 950915
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string *lines;
    string buff;
    int scr, err;

    if( !args ) return "你必须指定要查看尾部的文件。";
    else args = absolute_path(this_player()->query_cwd(), args);
    if( !file_exists(args) ) return "文件 " + args + " 未找到。";
    err = catch(buff = read_file(args));
    if( err || !buff ) return "无法查看尾部 " + args + "。";
    scr = ((this_player()->GetScreen())[1] || 24);
    if( scr > 100 ) scr = 100;
    if( sizeof(lines = explode(buff, "\n")) > scr ) 
        buff = implode(lines[<scr..], "\n");
    message("system", buff, this_player());
    return 1;
}

string GetHelp() {
    return ("语法: tail <文件>\n\n"
            "显示指定文件的最后若干行。\n"
            "另见: cat, head, more");
}
