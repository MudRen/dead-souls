#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
    if(!str){
        write("上帝模式: "+ (this_player()->GetGodMode() ? "开启" : "关闭"));
        return 1;
    }
    if(str == "on"){
        if(this_player()->GetGodMode()){
            write("你已经在上帝模式中了。\n");
            return 1;
        }
        this_player()->SetGodMode(1);
        if(this_player()->GetGodMode()){
            write("上帝模式已开启。");
        }
        else {
            write("失败。上帝模式未开启。");
        }
        return 1;
    }
    if(str == "off"){
        if(!(this_player()->GetGodMode())){
            write("你已经不在上帝模式中了。\n");
            return 1;
        }
        this_player()->SetGodMode(0);
        if(!(this_player()->GetGodMode())){
            write("上帝模式已关闭。");
        }
        else {
            write("失败。上帝模式仍然开启。");
        }
        return 1;
    }

    write("试试: help godmode");
    return 1;
}

string GetHelp(){
    return ("Syntax: godmode [ on | off ]\n\n"
            "Enables or disables immunity to most forms of lethal damage."); 
}
