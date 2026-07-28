/*    /secure/cmds/creator/ed.c
 *    from the Dead Souls LPC Library
 *    creator command to enter the editor
 *    created by Descartes of Borg 950406
 */

#include <lib.h>

inherit LIB_DAEMON;

int ed_callback(object ob){
    if(ob) ob->CheckCharmode();
    return 1;
}

mixed cmd(string args) {
    int x;

    if( args == "" || !args ) 
        args = user_path(this_player()->GetKeyName()) + "tmp.edit";
    if( this_player()->GetForced() ) {
        message("system", "有人试图强迫你编辑 "+ args +"\n" +
                identify(previous_object(-1)), this_player());
        return 0;
    }

    if(!this_player()->GetProperty("EdWarned")){
        write("这是你第一次使用ed。如果卡住了，只需按几次回车，"
                "然后在空行输入一个点，按回车，"
                "然后输入Q，再按回车。然后访问此页面了解更多关于"
                "ed编辑器的使用方法: http://dead-souls.net/editor.html");
        this_player()->SetProperty("EdWarned", 1);
    }
    args = absolute_path( this_player()->query_cwd(), args );
    if( (x = file_size(args)) == -2 )
        return "你不能编辑一个目录！";
    else if( x == -1 )
        message("editor", args + "，新文件，以输入模式开始。\n",
                this_player());
    else message("editor", args + "，" + x + " 字节\n", this_player());
    this_player()->eventEdit(args, (: ed_callback, this_player() :) );
    return 1;
}

string GetHelp() {
    return ("语法: ed [文件名]\n\n"
            "经典的 LP MUD 游戏内文本编辑器。它是行模式编辑器，\n"
            "意味着它古老、难用且复杂。但它是游戏内\n"
            "确定可用的编辑方式。\n"
            "简要指南:\n"
            "%^GREEN%^faq ed%^RESET%^\n"
            "详细文档:\n"
            "%^GREEN%^help editor%^RESET%^\n"
            "网页 FAQ，请使用浏览器访问: http://dead-souls.net/editor.html\n\n"
            "另见: ced, creweb, qcs");
}
