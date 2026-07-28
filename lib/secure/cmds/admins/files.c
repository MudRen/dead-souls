#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
string tmp;

mixed cmd(string args) {
    int x,c;
    string *filenames;
    string *ret_arr;

    if( !(master()->valid_apply(({ "ASSIST" }))) &&
            base_name(previous_object()) != "/secure/cmds/creators/findfun" && 
            base_name(previous_object()) != "/secure/cmds/creators/showfuns" )
        error("Illegal attempt to access file command: "+
                get_stack()+" "+identify(previous_object(-1)));

    if(args){
        if(grepp(args,"-x ")){
            args = replace_string(args,"-x ","");
            x = 1;
            tmp = args;
        }
        if(grepp(args,"-c ")){
            args = replace_string(args,"-c ","");
            c = 1;
            tmp = args;
        }
    }

    write("目录数量: "+sizeof(FILE_D->GetDirs()));
    filenames = FILE_D->GetFiles();
    write("文件数量: "+sizeof(filenames));
    if(!args || args == "")    return 1;
    if(!strsrch(args,"-x ")){
        args = replace_string(args,"-x ","");
        x = 1;
        tmp = args;
    }
    ret_arr = regexp(filenames, args);
    if(x) ret_arr = filter(ret_arr, (: !strsrch($1, tmp) :) );
    if(interactive(previous_object())){
        if(sizeof(implode(ret_arr,"\n"))) print_long_string(this_player(),implode(ret_arr,"\n"));
        else write("匹配结果过多。");
        return 1;
    }
    else return ret_arr;
}

string GetHelp() {
    return ("语法: files [-x] [-c] [子字符串]\n\n"
            "不带参数时，此命令重新加载文件守护进程的数据。"
            "如果给定子字符串，它还将搜索文件名并返回路径中"
            "包含该子字符串的文件。使用子字符串和 -x 标志时，"
            "它只返回路径以该子字符串*开头*的文件名。"
            "-c 标志跳过文件守护进程数据的重新加载，"
            "节省时间并避免全MUD延迟，但可能返回过时的信息。"
            "\n\n"
            "注意: 此命令用于查找文件已过时。"
            "在MUD中搜索文件请使用 \"find\" 命令。");
}
