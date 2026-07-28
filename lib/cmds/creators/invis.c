//      /bin/dev/_invis.c
//      from the Dead Souls mudlib
//      created by Descartes of Borg october 1992

#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(){
    if(this_player()->GetInvis()) {
        notify_fail("你已经隐身了。\n");
        return 0;
    }
    this_player()->SetInvis(1);
    message ("my_action", "你隐入阴影中。", this_player());
    return 1;
}

string GetHelp(){
    return ("语法：invis\n\n使你在任何情况下对低等级玩家不可见。\n另见：vis");
}
