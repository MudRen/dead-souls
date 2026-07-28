/*    /secure/cmds/creator/source.c
 *    from the Dead Souls LPC Library
 *    reads a file and forces you to execute each line as a command
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    string file, contents,flags,tmpargs;
    string *tmplines, *lines = ({});
    int queued, gauged;

    if(!args) {
        write("请指定一个文件作为参数。");
        return 1;
    }
    if(sscanf(args,"-%s %s",flags, tmpargs) == 2){
        args = tmpargs;
    }
    else flags = "";

    if(grepp(flags, "q")){
        queued = 1;
    }

    if(grepp(flags, "g")){
        if(query_os_type() != "windows"){
            gauged = 1;
        }
    }

    if(file_size(args) > 0 ) file = args;
    else if(file_size(this_player()->query_cwd()+"/"+args) > 0){
        file = this_player()->query_cwd()+"/"+args;
    }
    else {
        write("那不是一个有效的文件。");
        return 1;
    }

    if(!strsrch(file,"/secure/scripts/") ||
            !strsrch(file,user_path(this_player())) ){
        write("正在处理 "+file+"...");
    }
    else {
        write(file+" 不在允许的脚本目录中。中止。");
        return 1;
    }

    contents = read_file(file);

    if(!contents || !sizeof(contents)) {
        write("文件不可读或为空。");
        return 1;
    }

    tmplines = explode(contents,"\n");

    foreach(string line in tmplines){
        if(!strsrch(line,"title ") || !strsrch(line,"describe ")){
        }
        else {
            line = replace_string(line,"$N",this_player()->GetKeyName());
        }
        if(strsrch(line,"#")) lines += ({ (gauged ? "gauge " + line : line) });
    }

    if(queued){
        foreach( string line in lines ){
            if(line && line != "") write("排队命令: "+line);
            this_player()->eventQueueCommand(line);
        }
        this_player()->eventExecuteQueuedCommands();
        write("命令已排队。");
    }
    else {
        foreach( string line in lines ){
            if(line && line != "") write("执行命令: "+line);
            this_player()->eventForce(line);
        }
        write("脚本执行完成。");
    }
    return 1;

}

string GetHelp() {
    return ("语法: source [-gq] <文件名>\n\n"
            "如果文件存在且可读，此命令会读取文件的每一行，\n"
            "并强制你像在命令行输入一样执行每一行。\n"
            "如果你的主目录中有一个名为 .profile 的文件，\n"
            "每次登录时都会自动以这种方式执行它。\n\n"
            "要包含系统加载输出，使用 -g 标志。\n\n"
            "如果一组命令之间需要间隔时间\n"
            "（例如，避免 MAX_COMMANDS_PER_SECOND 限制），\n"
            "使用 -q 标志。例如:\n "
            "source -q /secure/scripts/crat2.src");
}
