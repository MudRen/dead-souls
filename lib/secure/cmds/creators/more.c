/*    /secure/cmds/creator/more.c
 *    from the Dead Souls Object Library
 *    more FILE
 *    created by Descartes of Borg 951104
 */

#include <lib.h>
#include <message_class.h>
#include "include/more.h"

inherit LIB_DAEMON;

mixed cmd(string str) {
    if( !str || str == "" ) return "语法: <more 文件>";
    return this_player()->eventPage(str, MSG_SYSTEM | MSG_NOCOLOUR);
}

string GetHelp(){
    return ("语法: more <文件>\n\n"
            "分页显示指定文件。在分页器中，你可以使用以下命令:\n" +
            LIB_PAGER->GetHelp("pager") + "\n\n"
            "另见: cat, ed, head, tail");
}
