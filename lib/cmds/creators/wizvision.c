#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
    if(!str){
        write("巫师视觉: "+ (this_player()->GetWizVision() ? "开启" : "关闭"));
        return 1;
    }
    if(str == "on"){
        if(this_player()->GetWizVision()){
            write("你的巫师视觉已经开启了。\n");
            return 1;
        }
        this_player()->SetWizVision(1);
        if(this_player()->GetWizVision()){
            write("巫师视觉已开启。");
        }
        else {
            write("失败。巫师视觉未开启。");
        }
        return 1;
    }
    if(str == "off"){
        if(!(this_player()->GetWizVision())){
            write("你的巫师视觉已经关闭了。\n");
            return 1;
        }
        this_player()->SetWizVision(0);
        if(!(this_player()->GetWizVision())){
            write("巫师视觉已关闭。");
        }
        else {
            write("失败。巫师视觉仍然开启。");
        }
        return 1;
    }
    write("试试: help wizvision");
    return 1;
}

string GetHelp(){
    return ("Syntax: wizvision [ on | off ]\n\n"+
            "Enables clear vision in all lighting situations."); 
}
