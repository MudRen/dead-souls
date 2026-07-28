#include <lib.h>
#include <dirs.h>
#include <commands.h>

inherit LIB_DAEMON;
string globalstr1, globalstr2;
int globalint;

mixed cmd(string str) {
    string *sorted_array, *sub_arr, *new_arr, *bkarr;
    string line, s1, bkname, bkcontents;
    int number;
    object here;

    if( !str ) return "你必须指定要恢复的文件。";
    if(str && sscanf(str,"%s %d",s1, number) > 1) str = s1;
    else false();

    new_arr = ({});
    sub_arr = ({});

    bkname = homedir(this_player())+"/bak/bk.db";

    if(!file_exists(bkname)) {
        write("备份数据库文件不存在。中止操作。");
        return 1;
    }

    bkcontents = read_file(bkname);
    bkarr = explode(bkcontents,"\n");

    foreach(string zline in bkarr){
        if(!strsrch(zline,str)) new_arr += ({ zline });
    }

    if(!sizeof(new_arr) && str == "here"){
        here = environment(this_player());
        str = last_string_element(base_name(here),"/");
        foreach(string zline in bkarr){
            if(!strsrch(zline,str)) new_arr += ({ zline });
        }
    }

    if(!sizeof(new_arr)){
        write("你没有备份过该名称的文件。");
        return 1;
    }

    if(str == "workroom.orig") {
        unguarded( (: globalint = cp(homedir(this_player())+"/bak/workroom.orig",
                        homedir(this_player())+"/workroom.c") :) );
        if(globalint) {
            write("工作室文件已恢复。");
            load_object(CMD_UPDATE)->cmd("-a "+homedir(this_player())+"/workroom.c");
        }
        else write("工作室无法恢复。");
        return 1;
    }

    foreach(string zline in bkarr){
        if(strsrch(zline,str) != -1) new_arr += ({ zline });
    }

    if(!number || number < 1) number = 1;
    sorted_array = sort_array(new_arr, -1);
    if(number > sizeof(sorted_array)) number = sizeof(sorted_array);
    line = sorted_array[(number - 1)];

    sub_arr = explode(line," : ");
    if(!file_exists(REALMS_DIRS + "/" + this_player()->GetKeyName()+"/bak/"+sub_arr[0])){
        write("该文件在备份数据库中有记录，但在备份目录中找不到。");
        return 1;
    }
    globalstr1 = REALMS_DIRS + "/" + this_player()->GetKeyName()+"/bak/"+sub_arr[0];
    globalstr2 = sub_arr[1];
    cp(globalstr1, globalstr2);
    if(here) reload(here);
    write("文件已恢复。");
    return 1;
}

string GetHelp(){
    return ("语法: restore <文件名> [数字]\n\n"
            "从你的 bak/ 目录恢复指定文件。\n"
            "如果指定了数字，命令会尝试找到第 N 新的文件来恢复。示例:\n"
            "恢复 file.c 的最新版本:\n"
            "restore file.c\n"
            "恢复最近一次备份之前的版本:\n"
            "restore file.c 2\n"
            "依此类推。\n"
            "\"restore here\" 会尝试恢复你当前所在房间的备份，\n"
            "并在可能的情况下重新加载。这是唯一会自动重新加载\n"
            "恢复对象的情况。\n"
            "另见: bk");
}
