#include <lib.h>

inherit LIB_DAEMON;

varargs int cmd(string str){
    if(!str){
        write("骚扰屏蔽当前"+ (this_player()->GetAnnoyblock() ? "开启。" : "关闭。"));
        return 1;
    }
    if(str == "on"){
        if(this_player()->GetAnnoyblock()){
            write("你的骚扰屏蔽已经处于开启状态。\n");
            return 1;
        }
        this_player()->SetAnnoyblock(1);
        if(this_player()->GetAnnoyblock()){
            write("骚扰屏蔽已开启。");
        }
        else {
            write("失败，骚扰屏蔽未能开启。");
        }
        return 1;
    }
    if(str == "off"){
        if(!(this_player()->GetAnnoyblock())){
            write("你的骚扰屏蔽已经处于关闭状态。\n");
            return 1;
        }
        this_player()->SetAnnoyblock(0);
        if(!(this_player()->GetAnnoyblock())){
            write("骚扰屏蔽已关闭。");
        }
        else {
            write("失败，骚扰屏蔽仍然开启。");
        }
        return 1;
    }
    write("试试: help annoyblock");
    return 1;
}

string GetHelp(){
    return ("用法: annoyblock [ on | off ]\n\n"
            "屏蔽烦人的消息，如\"Joe looks around.\"");
}
