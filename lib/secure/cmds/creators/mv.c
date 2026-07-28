/*
// This file is part of the TMI Mudlib distribution.
// Please include this header if you use this code.
// Adapted by Buddha(1-18-91) from unknown source.
// Added check for existance of destination file. Plura 930120
 */

#include <lib.h>
inherit LIB_DAEMON;

int cmd(string str);
string GetHelp();


mixed cmd(string str){
    string t1, t2, *tmp;
    int force = 0;
    int dir = 0;
    if(this_player()->GetForced()) {
        write("有人试图强迫你移动 "+str+"\n");
        return 1;
    }

    if(!str || !sizeof(str)){
        return GetHelp();
    }

    if(sscanf(str,"-f %s %s",t1,t2) == 2) {
        force = 1;
        str = t1+" "+t2;
    }
    if(!str||sscanf(str,"%s %s",t1,t2)!=2) {
        /* We should add checks for flags here. */
        return GetHelp();  
    } else {
        if(!force){
            if(file_size(t2=absolute_path(this_player()->query_cwd(),t2)) > 0)
            {
                notify_fail("mv: "+t2+" 已存在。\n");
                return 0;
            }
        }
        t1=absolute_path(this_player()->query_cwd(),t1);
        t2=absolute_path(this_player()->query_cwd(),t2);
        if(directory_exists(t1)) dir = 1;
        else if(file_exists(t1)) dir = 0;
        else {
            write(t1+": 没有该文件或目录。");
            return 1;
        }
        if(!dir && directory_exists(t2)){
            if(last(t2,1) != "/") t2 += "/";
            t2 += last_string_element(t1,"/");
        } 
        rename(t1,t2);
        if((dir && directory_exists(t2) && !directory_exists(t1)) ||
                (!dir && file_exists(t2) && !file_exists(t1)) )
            write("mv: 完成。");
        else write("mv: 失败。");
    }
    return 1;
}

string GetHelp() {
    return "语法: mv <文件1> <文件2|目录>\n\n"
        "重命名文件或将其移动到指定目录。\n"
        "-f 标志强制覆盖已存在的文件。\n\n"
        "示例:\n"+
        "mv -f workroom.bak workroom.c\n"+
        "mv workroom.bak /tmp/\n\n"
        "另见: rm";
}
