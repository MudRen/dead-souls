#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    if(!sizeof(args) || (args != "on" && args != "off") ){
        write("语法：pk [ on | off ]");
        return 1;
    }
    if(args == "off"){
        if(creatorp(this_player())){
            if(!(this_player()->GetPK())) write("你的PK标志已经是关闭状态。");
            else write("你的PK标志现在已关闭。");
            this_player()->SetPK(0);
            return 1;
        }
        else {
            write("你必须请求创建者来禁用你的PK标志。");
            return 1;
        }
    }
    if((this_player()->GetPK())){
        write("你已经是玩家杀手了。");
        return 1;
    }
    if(this_player()->GetProperty("PK warned")){
        this_player()->SetProperty("PK warned",0);
        write("你现在是一个玩家杀手。");
        this_player()->SetPK(1);
        return 1;
    }
    else {
        write("如果你启用PK标志，只有创建者才能禁用它。");
        write("如果你100%确定想要PK，请再次输入该命令。");
        this_player()->SetProperty("PK warned",1);
        return 1;
    }
}

string GetHelp() {
    return ("语法：pk [ on | off ]\n\n"
            "\t除非你被设置为玩家杀手，否则你不能参与玩家对战。"
            "此命令切换你的玩家杀手设置。一旦被设置为PK，玩家不能"
            "在没有创建者干预的情况下取消它。\n"
            "\t玩家杀戮还需要MUD在其配置文件中启用全局PK设置，"
            "并且你所在的房间也必须启用PK。\n"
            "另见：env");
}
