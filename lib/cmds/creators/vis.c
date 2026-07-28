//      /bin/dev/_vis.c
//      from the Dead Souls mudlib
//      created by Descartes of Borg october 1992

#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
    if(!this_player()->GetInvis()){
        notify_fail("你已经可见了。\n");
        return 0;
    }
    this_player()->SetInvis(0);
    message ("my_action", "你从阴影中走出。", this_player());
    return 1;
}

string GetHelp(){
    return "语法：vis\n\n"
        "使你变为可见状态。"
        "\n另见：invis";
}
