/*
// This file is part of the TMI Mudlib distribution
// Please include this header if you use this code.
// Written by Sulam(1-8-92)
// Help added (1/28/92) by Brian
 */

#include <lib.h>
inherit LIB_DAEMON;

string GetHelp();

mixed cmd(string str){
    if( !str )
    {
        return GetHelp();
    }
    str = absolute_path(this_player()->query_cwd(), str);
    switch( file_size(str) )
    {
        case -1:
            notify_fail("rmdir: "+str+": 没有该文件。\n");
            return 0; break;
        case -2:
            break;
        default:
            notify_fail("rmdir: "+str+": 不是目录。\n");
            return 0; break;
    }
    if( master()->valid_write(str, this_object(), "rmdir") == 0 )
    {
        notify_fail(str+": 权限被拒绝。\n");
        return 0;
    }
    write(rmdir(str) ? "完成。\n" : str+": 无法删除目录。\n");
    return 1;
}

string GetHelp(){
    return ("语法: rmdir <目录>\n\n"+
            "此命令允许你删除指定目录。\n"
            "如果目录不为空，命令将失败。");
}
