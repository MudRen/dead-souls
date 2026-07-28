/*    /secure/cmds/creator/cat.c
 *    from the Foundation II LPC Library
 *    command to display file contents
 *    created by Descartes of Borg 940124
 *    some updates made 950915
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string *arr;
    string tmp;

    if( !str ) return "你必须指定要查看的文件。";
    else str = absolute_path(this_player()->query_cwd(), str);
    if( !file_exists(str) ) return "文件 " + str + " 未找到。";
    else if( !(tmp = read_file(str)) )
        return "无法读取文件 " + str + "。";
    if( sizeof(arr = explode(tmp, "\n")) > 100 )
        tmp = implode(arr[0..99], "\n") + "\n\t***  已截断  ***";
    message("system", tmp, this_player());
    return 1;
}

string GetHelp(){
    return ("语法: cat <文件>\n\n"
            "一次性显示指定文件的内容。\n"
            "如果文件过长，输出可能会被截断。\n"
            "另见: longcat");
}
