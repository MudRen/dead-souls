#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if(!sizeof(args) || (args != "on" && args != "off") ){
        write("用法: pk [ on | off ]");
        return 1;
    }
    if(args == "off"){
        if(creatorp(this_player())){
            if(!(this_player()->GetPK())) write("你的PK标志已经关闭。");
            else write("你的PK标志已关闭。");
            this_player()->SetPK(0);
            return 1;
        }
        else {
            write("你必须请创造者来关闭你的PK标志。");
            return 1;
        }
    }
    if((this_player()->GetPK())){
        write("你已经是玩家杀手了。");
        return 1;
    }
    if(this_player()->GetProperty("PK warned")){
        this_player()->SetProperty("PK warned",0);
        write("你现在是玩家杀手了。");
        this_player()->SetPK(1);
        return 1;
    }
    else {
        write("如果你启用PK标志，只有创造者才能关闭它。");
        write("如果你100%确定要PK，请再次输入命令。");
        this_player()->SetProperty("PK warned",1);
        return 1;
    }
}

string GetHelp() {
    return ("用法: pk [ on | off ]\n\n"
            "\t除非你被设置为玩家杀手，否则你无法参与"
            "玩家对战。此命令切换你的玩家杀手设置。"
            "一旦设置为PK，玩家无法自行取消，需要创造者介入。\n"
            "\t玩家杀戮还需要mud在其配置文件中启用全局PK设置，"
            "并且你所在的房间也必须启用PK。\n"
            "参考: env");
}
