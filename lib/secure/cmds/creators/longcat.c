#include <lib.h>
#include <runtime_config.h>

inherit LIB_DAEMON;

nosave int send_queued_mess(string tmp, object whom){
    message("receive", tmp, whom);
    return 1;
}

mixed cmd(string str) {
    string *arr;
    mixed tmp;
    int delay = -1;
    int bmax = (__LARGEST_PRINTABLE_STRING__ - 1024);
    int chunks, rem, currchunk, smax = (get_config(__MAX_STRING_LENGTH__) - 10);

    if( !str ) return "你必须指定要查看的文件。";
    else str = absolute_path(this_player()->query_cwd(), str);
    if( !file_exists(str) ) return "文件 " + str + " 未找到。";
    if((tmp = file_size(str)) < smax){
        if( !(tmp = read_file(str)) )
            return "无法读取文件 " + str + "。";
        arr = explode(tmp,"\n");
        foreach(string line in arr){
            message("system", line, this_player());
        }
        return 1;
    }
    chunks = tmp / bmax;
    rem = tmp % bmax;
    if(rem) chunks++;
    while(chunks){
        delay++;
        chunks--;
        if(chunks){
            tmp = read_bytes(str, currchunk, bmax);           
            currchunk += bmax;
        }
        if(rem && !chunks){
            tmp = read_bytes(str, currchunk, rem);
            currchunk += rem;
        }
        call_out("send_queued_mess", (delay/5), tmp, this_player());
    }
    return 1;
}

string GetHelp() {
    return ("语法: longcat <文件>\n\n"
            "    /\___/\ \n"
            "   /       \ \n"
            "  |  #    # | \n"
            "  \     @   | \n"
            "   \   _|_ / \n"
            "   /       \______ \n"
            "  / _______ ___   \ \n"
            "  |_____   \   \__/ \n"
            "   |    \__/ \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   |       | \n"
            "   /        \ \n"
            "  /   ____   \ \n"
            "  |  /    \  | \n"
            "  | |      | | \n"
            " /  |      |  \ \n"
            " \__/      \__/ \n"
            "一次性显示指定文件的全部内容，不限制输出大小。\n"
            "注意：过大的文件可能会导致延迟，\n"
            "并可能因\"求值时间过长\"而报错。");
}
