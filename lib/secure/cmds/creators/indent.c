#include <lib.h>

inherit LIB_DAEMON;

string cmd(string str) {

    string *files, *paths;
    string where, rulefile, tmp;
    int flag;

    notify_fail("语法: <indent [文件 | * | */*]\n");

    if( !str ) return "你必须指定文件或通配符。";
    else if(str == "*") flag = 1;
    else if(str == "*/*") flag = 2;
    else str = absolute_path(this_player()->query_cwd(), str);
    if( !file_exists(str) && !flag) return "文件 " + str + " 未找到。";
    else if( !(tmp = read_file(str)) && !flag)
        return "无法读取文件 " + str + "。";

    rulefile = "/tmp/"+this_player()->GetKeyName()+".indent";
    write_file(rulefile, "I",1);

    if(flag){

        where = this_player()->query_cwd();
        if(flag == 1) paths = ({ where });
        else {
            paths = ({});
            files = get_dir(this_player()->query_cwd()+"/");
            if(sizeof(files)) foreach(string s1 in files){
                if(file_size(where + "/" +s1) == -2 ){
                    paths += ({ where + "/" +s1 });
                }
            }
        }
        if(sizeof(paths)) foreach(string path in paths){
            load_object("/secure/cmds/creators/lsed")->cmd(rulefile + " "+ path + "/*.c");
            load_object("/secure/cmds/creators/lsed")->cmd(rulefile + " "+ path + "/*.h");
        }
    }

    else {
        load_object("/secure/cmds/creators/lsed")->cmd(rulefile + " "+str);
    }

    rm(rulefile);
    return "完成。";
}

string GetHelp() {
    return ("语法: indent [文件 | * | */*]\n\n"
            "对指定文件或目录中的所有文件进行缩进格式化。"
            "\n另见: cd, ls, mv, pwd, rm, lsed, grep");
}
