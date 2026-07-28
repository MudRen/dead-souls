#include <lib.h>
#include <commands.h>
#ifndef CED_DISABLED 
#define CED_DISABLED 1
#endif

inherit LIB_DAEMON;

mixed cmd(string args) {
    int x = this_player()->GetCharmode();

    if( args == "" || !args ) 
        args = user_path(this_player()->GetKeyName()) + "tmp.edit";
    if( this_player()->GetForced() ) {
        message("system", "有人试图强迫你编辑 "+ args +"\n" +
                identify(previous_object(-1)), this_player());
        return 0;
    }

    if(!x){
        write("使用此命令需要字符模式。更多信息请查看: help charmode");
        return 1;
    }

    if(!this_player()->GetProperty("cedWarned")){
        write("这是你第一次使用ced。如果卡住了，只需按: Ctrl-Q");
        this_player()->SetProperty("cedWarned", 1);
    }
    args = absolute_path( this_player()->query_cwd(), args );
    if( (x = file_size(args)) == -2 ) 
        return "你不能编辑目录！";
    else if( x == -1 )
        message("editor", args + "，新文件，开始输入模式。\n",
                this_player());
    else message("editor", args + ", " + x + " bytes\n", this_player());
    CMD_BK->cmd(args);
    this_player()->SetCedmode(1, args);
    return 1;
}

string GetHelp(){
    string ret = "";
    ret += "Syntax: ced [FILE]\n\n";
    ret += "This command starts a character-mode editing session on the "+
        "specified file. Note that without charmode enabled, this "+
        "will not work. Special commands are issued by pressing the "+
        "\"Control\" key and another key at the same time. For "+
        "example, to quit without saving, you press and hold "+
        "the control key, then the 'q' key. This is known as Ctrl-Q. "+
        "The special commands for ced are:\n\n"+
        "Ctrl-Q -- quit without saving\n"+
#if CED_DISABLED
        "Ctrl-X -- %^RED%^DISABLED FUNCTION%^RESET%^\n"+
        "Ctrl-S -- %^RED%^DISABLED FUNCTION%^RESET%^\n"+
#else
        "Ctrl-X -- quit and save\n"+
        "Ctrl-S -- save\n"+
#endif
        "Ctrl-I -- enable insert mode\n"+
        "Ctrl-O -- enable overstrike mode\n"+
        "Ctrl-L -- refresh the page\n"+
        "Ctrl-F -- scroll forward one page\n"+
        "Ctrl-B -- scroll backward one page\n"+
        "Ctrl-D -- delete current line\n"+
        "Ctrl-G -- Specify a line to go to\n"+
        "Ctrl-/ -- Search for a string\n"+
        "\nTo navigate in the screen, use the arrow keys on your keyboard. "+
        "Note that ced is extremely basic and experimental. "+
        "\nSee also: ed, charmode, bk, restore, env"+
#if CED_DISABLED
        "\n\n Please note that due to its alpha status, saving files in "+
        "ced is disabled for now."+
#endif
        "";
    return ret;
}
