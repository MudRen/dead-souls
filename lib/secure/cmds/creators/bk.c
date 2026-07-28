#include <lib.h>
#include <dirs.h>

inherit LIB_DAEMON;

mixed cmd(string str) {
    string *file_arr;
    string tmp, filename, str2, orig;
    int time;
    object ob;

    orig = str;
    if( !str ) return "你必须指定要备份的文件。";
    else str = absolute_path(this_player()->query_cwd(), str);
    if( !file_exists(str) ) str2 = str+".c";
    if( !file_exists(str) && !file_exists(str2)) {
        if(str == "here" || str == "room") ob = environment(this_player());
        else {
            ob = present(orig,environment(this_player()));
            if(!ob) ob = present(orig, this_player());
            if(!ob) return "文件未找到。";
        }
        str2 = base_name(ob)+".c";
    }
    if(str2 && !file_exists(str2)) return "文件未找到。";
    else if(str2) str = str2;
    if( !(tmp = read_file(str)) )
        return "无法读取文件 " + str + "。";

    else {
        time = time();
        file_arr = explode(str,"/");
        filename = REALMS_DIRS + "/" + this_player()->GetKeyName();
        filename += "/bak/"+file_arr[sizeof(file_arr)-1]+"."+time;
        write_file(REALMS_DIRS + "/" + this_player()->GetKeyName()+
                "/bak/bk.db",file_arr[sizeof(file_arr)-1]+"."+time+" : "+str+"\n");
        load_object("/secure/cmds/creators/cp")->cmd(str + " " +filename);
    }
    return 1;
}

string GetHelp(){
    return ("语法: bk [文件]\n"
            "        bk here\n\n"
            "将指定文件复制到你的 bak/ 目录，\n"
            "并在备份文件名后追加唯一的标识数字。\n"
            "另见: restore, find, reload");
}
