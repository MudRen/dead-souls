/*    /secure/cmds/creator/lsed.c
 *    from the Dead Souls LPC Library
 *    an LPC scripted editor
 *    created by Descartes of Borg 950407
 */

#include <lib.h>

inherit LIB_DAEMON;

protected void LsedFile(string file, string *cmds, int num_cmds);

mixed cmd(string args) {
    string *files, *lines, *tmp;
    string total, script, pwd;
    int i, maxi, x;

    if( args == "" || !args ) return "语法: <lsed [脚本] [文件列表]>";
    if( (maxi = sizeof(files = explode(args, " "))) == 1 )
        return "你必须指定要运行脚本的文件名。";
    pwd = this_player()->query_cwd();
    script = absolute_path( pwd, files[0] );
    files = files[1..];
    maxi--;
    for(i=0, tmp = ({}); i<maxi; i++) {
        files[i] = absolute_path(pwd, files[i]);
        tmp += wild_card(files[i]);
    }
    maxi = sizeof(files = tmp);
    if( !(total = read_file(script)) ) return "加载脚本失败: "+script;
    x = sizeof(lines = explode(total, "\n"));
    for(i=0; i<maxi; i++){
        int y;

        y = file_size(files[i]);
        if( y == -2 ) {
            message("system", "lsed: 文件 " + files[i] + " 是一个目录。",
                    this_player());
            continue;
        }
        else if( y == -1 ) {
            message("system", "lsed: 文件 " + files[i] + " 不存在。",
                    this_player());
            continue;
        }
        LsedFile(files[i], lines, x);
    }
    return 1;
}

protected void LsedFile(string file, string *cmds, int num_cmds) {
    string ret;
    int i;

    ed_start(file, 0);
    if( query_ed_mode() == -1 ) {
        message("system", "lsed: 读取文件失败 " + file, this_player());
        return;
    }
    for(i=0; i<num_cmds; i++) {
        ret = ed_cmd(cmds[i]);
        if( query_ed_mode() == -1 ) {
            message("system", "lsed: 脚本在第 " +
                    (i+1) + " 行意外退出，文件 " + file + "，消息: " + ret,
                    this_player());
            return;
        }
    }
    ret = ed_cmd("x");
    if( query_ed_mode() != -1 ) {
        ed_cmd("Q");
        message("system", "lsed: 权限被拒绝: " + file,
                this_player());
        return;
    }
    message("system", ret, this_player());
}

string GetHelp() {
    return ("语法: lsed <脚本> <文件列表>\n\n"
            "允许你通过脚本对文件或文件集执行编辑器命令。\n"
            "你只需编写一个编辑器命令脚本并保存到文件。\n"
            "例如，要将主目录下所有文件中的\n"
            "set_item_functions() 改为 SetItems()，\n"
            "set_search_function() 改为 SetSearch()，\n"
            "编写如下脚本:\n\n"
            "s/set_item_functions/SetItems/g\n"
            "s/set_search_function/SetSearch/g\n\n"
            "保存为 convert.lsed，然后在命令行输入:\n"
            "\"lsed convert.lsed *\"。\n"
            "注意 MudOS 驱动对执行线程有时间限制，\n"
            "避免一次对大量文件运行 lsed。\n"
            "另见: ed");
}

