/*    /cmds/player/screen.c
 *    from the Foundation II LPC Library
 *    sets width and height for player terminals
 *    created by Descartes of Borg 950328
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    int *screen;
    int h, w, lock = this_player()->GetProperty("screenlock");
    string chide = "你需要同时指定宽度和高度。\n";
    string ret = "你当前的设置是: "+ this_player()->GetScreen()[0];
    ret += " "+ this_player()->GetScreen()[1];

    if( args == "" || !args )
        return chide + ret;
    this_player()->SetProperty("screenlock", 0);
    if( sscanf(args, "%d %d", w, h) != 2 )
        return chide + ret;
    this_player()->SetScreen(w, h);
    message("system", "屏幕已设置为 " + w + " x " + h + "。", this_player());
    this_player()->SetProperty("screenlock", lock);
    return 1;
}

string GetHelp() {
    return ("用法: screen [宽度 高度]\n\n"
            "设置你电脑屏幕的尺寸，以便 "+mud_name()+
            " 知道如何向你的屏幕发送信息。\n"
            "参考: screenlock, brief, terminal, env");
}
