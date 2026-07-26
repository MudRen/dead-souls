/*    /cmds/player/faq.c
 *    from the Foundation II LPC Library
 *    a command to access Frequently Asked Questions lists easily
 *    created by Descartes of Borg 950501 (power to the proletariate)
 */

#include <lib.h>

inherit LIB_DAEMON;

protected void GetFAQ(string args);

mixed cmd(string args) {
    if( !args || args == "" ) {
        string *files;
        int cols, i, maxi, x, y;

        message("help", mud_name() + " 有以下常见问题列表:",
                this_player());
        cols = ((int *)this_player()->GetScreen())[0];
        i = sizeof(files = get_dir(DIR_FAQS "/"));
        while(i--) if( (y =strlen(files[i])) > x ) x = y;
        cols = cols / (x+2);
        message("help", format_page(files, cols), this_player());
        message("prompt", "\n查看哪个常见问题（默认为 general）？ ", this_player());
        input_to( (: GetFAQ :) );
        return 1;
    }
    else GetFAQ(args);
    return 1;
}

protected void GetFAQ(string args) {
    string file;
    //bugfix courtesy of Manchi
    if( !args || args == "" || args == "y" || args == "Y" || lower_case(args) == "yes")
        args = "general";
    if( file_size(file = DIR_FAQS "/" + args) < 0 ) {
        message("error", "没有此常见问题。", this_player());
        return;
    }
    if( !(file = read_file(file)) ) {
        message("error", "读取常见问题文档失败。", this_player());
        return;
    }
    this_player()->eventPage(explode(file, "\n"), "help");
}

string GetHelp() {
    return ("用法: faq [常见问题]\n\n"
            "如果你指定了要阅读的常见问题，此命令将为你显示该问题。"
            "如果没有指定，它会给你一个常见问题列表供你选择。"
            "FAQ 代表常见问题。阅读常见问题是了解 " +
            mud_name() + " 基本主题的好方法。\n"
            "参考: help" + (creatorp(this_player()) ? ", man" : ""));
}


