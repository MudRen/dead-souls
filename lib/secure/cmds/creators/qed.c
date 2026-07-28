/*    /secure/cmds/creator/ed.c
 *    from the Dead Souls LPC Library
 *    creator command to enter the editor
 *    created by Descartes of Borg 950406
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

int UnMuff(object whom){
    if(!whom) whom = this_player();
    whom->eventPauseMessages(0);
    return 1;
}

mixed cmd(string args) {
    int x;

    if( args == "" || !args ) 
        args = user_path(this_player()->GetKeyName()) + "tmp.edit";
    if( this_player()->GetForced() ) {
        message("system", "Someone tried to force you to edit "+ args +"\n" +
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
    this_player()->eventPauseMessages(1,MSG_EDIT);
    this_player()->eventEdit(args, (: UnMuff(this_player()) :) );
    return 1;
}

string GetHelp() {
    return ("语法: qed [文件名]\n\n"
            "这是 ed 的安静版本。编辑时，你只会收到编辑数据和一些有限的消息。"
            "编辑完成后，你会看到错过的游戏消息。"
            "请小心使用此命令的位置，因为你可能会在编辑期间"
            "参与战斗并被杀死而不自知。\n"
            "另见: ed, ced, qcs, creweb");
}
