/*    /secure/cmd *    from Dead Souls 3.2.2
 *    access granting command to allow cres to give out private access
 *    created by Descartes of Borg 940918
 */

#include <lib.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string *tmp = ({});
    string type, file, who, path;

    if(!str) return notify_fail("语法: grant [权限] to [谁] on [文件]\n");
    else if(sscanf(str, "%s to %s on %s", type, who, file) != 3)
        return notify_fail("语法: grant [权限] to [谁] on [文件]\n");
    if(sizeof(tmp = explode(file, "/")) < 2)
        return notify_fail("你无法授予此类权限。\n");
    if(tmp[0] != "domains" && tmp[0] != "realms" && tmp[0] != "estates")
        return notify_fail("你无法授予此类权限。\n");
    path = homedir(this_player()) + "/";
    if(file_size(path+"adm") != -2) mkdir(path+"adm");
    file = absolute_path(this_player()->query_cwd(), file);
    if(!file_exists(path+"adm/access.c"))
        write_file(path+"adm/access.c", "#include <lib.h>\n\ninherit LIB_ACCESS;\n");
    if(file_size(file) == -2 && file[strlen(file)-1] != '/') file = file + "/";
    if(type == "read" || type == "all") {
        if(!(call_other(path+"adm/access","grant_access","read",file,who)))
            return notify_fail("读权限授予失败！\n");
        if( file_size(file) == -2 ) {
            if( !(call_other(path + "adm/access", "grant_access", "read",
                            file[0..<2], who)) )
                return notify_fail("读权限授予失败。\n");
        }
    }
    if(type == "write" || type == "all") {
        if(!(call_other(path+"adm/access","grant_access","write",file,who)))
            return notify_fail("写权限授予失败！\n");
        if( file_size(file) == -2 ) {
            if( !(call_other(path + "adm/access", "grant_access", "write",
                            file[0..<2], who)) )
                return notify_fail("写权限授予失败。\n");
        }
    }
    message("system", capitalize(type) + " 权限已授予 " + who + "，文件: " + file + "。",
            this_player());
    return 1;
}

string GetHelp(){
    return ("语法: grant <权限类型> to <对象> on <文件|目录>\n\n"
            "允许你授予其他创造者对你控制下的文件或目录的访问权限。\n"
            "权限类型参数为 \"read\"、\"write\" 或 \"all\"。\n"
            "没有\"取消授权\"或\"拒绝\"命令。");
}
