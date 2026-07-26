#include <lib.h>

inherit LIB_DAEMON;

string ReportSyntax(){
    int admin = adminp(this_player());
    string ret = "用法: gag [remote 或 local] <on 或 off>";
    if(admin) ret += "        gag <玩家> [on 或 off]";
    return ret;
}

mixed cmd(string str) {
    string which, type;
    object player;
    string *validtypes = ({ "remote", "local", "all" });
    int admin = adminp(this_player());
    if( !sizeof(str) )
        return ReportSyntax();
    str = lower_case(str);
    sscanf(str,"%s %s", type, which);
    if(!which && type){
        which = type;
        type = "all";
    }
    if(!type){
        if(admin){
            player = find_player(str);
        }
        if(!player) which = str;
        else which = "on";
        type = "all";
    }
    if(admin){
        if(!player) player = find_player(type);
        if(player){
            if(!which) which = "on";
            type = "all";
        }
    }
    if( which != "on" && which != "off" )
        return "你只能将 gag 设置为 'on' 或 'off'。";
    if( !player && member_array(type, validtypes) == -1 )
        return "有效的 gag 类型有: remote, local, all。";
    if(!player) player = this_player();
    if(admin){
        player->SetGagged(type, (which == "on" ? 2 : 0));
    }
    else {
        player->SetGagged(type, (which == "on"));
    }
    message("system",
            "禁言模式已为 "+type+" 频道"+str+
            (player != this_player() ? "（针对 "+player->GetName()+"）" : "")+
            " 开启。", this_player() );
    return 1;
}

string GetHelp() {
    int admin = adminp(this_player());
    return "用法: gag [remote | local] <on | off>\n"+
        (admin ? "        gag <玩家> <on | off>\n" : "")+
        "\n此命令阻止你在频道上说话。\n"
        "当你隐藏或使用多个角色时很有用。\n"
        "你可以用 gag on 禁言所有频道\n"
        "你可以用 gag remote on 仅禁言跨mud频道\n"
        "参考: mute, env";
}
