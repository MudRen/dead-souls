#include <lib.h>

inherit LIB_DAEMON;

string GetMuted(){
    string ret;
    if(this_player()->GetMutedType("local")){
        ret = "本地: %^RED%^已静音%^RESET%^";
    }
    else {
        ret = "本地: %^GREEN%^收听中%^RESET%^";
    }
    if(this_player()->GetMutedType("remote")){
        ret += ", 远程: %^RED%^已静音%^RESET%^";
    }
    else {
        ret += ", 远程: %^GREEN%^收听中%^RESET%^";
    }
    return ret;
}

string GetGagged(){
    string ret;
    if(this_player()->GetGaggedType("local")){
        ret = "本地: %^RED%^已禁言%^RESET%^";
    }
    else {
        ret = "本地: %^GREEN%^可发言%^RESET%^";
    }
    if(this_player()->GetGaggedType("remote")){
        ret += ", 远程: %^RED%^已禁言%^RESET%^";
    }
    else {
        ret += ", 远程: %^GREEN%^可发言%^RESET%^";
    }
    return ret;
}

mixed cmd(string args) {
    object player = this_player();
    mixed replee = player->GetProperty("reply");
    string ret = "";
    string *tmp;
    ret += "屏幕: \t\t"+identify(this_player()->GetScreen())+"\n";
    ret += "终端: \t\t"+this_player()->GetTerminal()+"\n";
    ret += "简略模式: \t\t"+ ( (this_player()->GetBriefMode()) ? "开" : "关" )+"\n";
    ret += "过滤器: \t\t"+ ( (this_player()->GetParanoia("cursefilter")) ? "开" : "关" )+"\n";
    ret += "频道消息颜色: "+ ( (this_player()->GetNoChanColors()) ? "关" : "开" )+"\n";
    ret += "玩家杀手模式: \t"+ ( (this_player()->GetPK()) ? "开" : "关" )+"\n";
    ret += "静音模式: \t\t"+ GetMuted()+" \n";
    ret += "禁言模式: \t\t"+ GetGagged()+" \n";
    ret += "逃跑模式: \t\t"+ ( (this_player()->GetWimpy()) ? "开" : "关" )+"\n";
#if efun_defined(compressedp)
    ret += "MCCP模式: \t\t"+(compressedp(this_player()) ? "开" : "关")+"\n";
#endif
#if MINIMAP
    ret += "小地图模式: \t\t"+ ( this_player()->GetProperty("minimapping") ? "开" : "关" )+"\n";
#endif
    ret += "屏蔽功能: \t\t"+ ( (this_player()->GetAnnoyblock()) ? "开" : "关" )+"\n";
    ret += "重提示模式: \t\t"+ ( this_player()->GetProperty("reprompt") ? "开" : "关" )+"\n";
    ret += "屏幕锁定模式: \t"+ ( this_player()->GetProperty("screenlock") ? "开" : "关" )+"\n";
    ret += "时区: \t\t"+ ( this_player()->GetProperty("timezone") ?
            this_player()->GetProperty("timezone") : "未指定" )+"\n";
#ifdef __GET_CHAR_IS_BUFFERED__
    ret += "字符模式: \t\t"+
        //( (query_charmode(player) > 0) ? "开" : "关" )+"\n";
        ( (player->GetCharmode()) ? "开" : "关" )+"\n";
#endif
    ret += "命令回显: \t\t"+ ( this_player()->GetProperty("commandecho") ? this_player()->GetProperty("commandecho") : "关" )+"\n";
#ifdef __DSLIB__
    ret += "保活模式: \t"+ ( this_player()->GetProperty("keepalive")
            ? this_player()->GetProperty("keepalive") : "关" )+"\n";
#endif

    if(creatorp(this_player())){
        ret += "主目录: \t\t"+user_path(this_player())+"\n";
        if(this_player()->GetParanoia("homeroom")){
            ret += "主房间: \t\t"+this_player()->GetParanoia("homeroom")+"\n";
        }
        ret += "调试模式: \t\t"+ ( (this_player()->GetProperty("debug")) ? "开" : "关" )+"\n";
        ret += "上帝模式: \t\t"+ ( (this_player()->GetGodMode()) ? "开" : "关" )+"\n";
        ret += "巫师视野: \t\t"+ ( (this_player()->GetWizVision()) ? "开" : "关" )+"\n";
#if GRID
        ret += "显示网格: \t\t"+ ( (this_player()->GetVisibleGrid()) ? "开" : "关" )+"\n";
        ret += "巫师地图模式: \t\t"+ ( this_player()->GetProperty("wizmapping") ? "开" : "关" )+"\n";
        ret += "无碰撞模式: \t\t"+ ( this_player()->GetProperty("noclip") ? "开" : "关" )+"\n";
        ret += "锚定: \t\t"+ ( this_player()->GetAnchored() ? "开" : "关" )+"\n";
#endif
    }
    if(replee){
        ret += "回复目标: \t\t"+replee+"\n";
    }
    tmp = sort_array(explode(ret, "\n"),1);
    ret = implode(tmp, "\n");
    write(ret);
    return 1;
}

string GetHelp() {
    string *see_also = ({});
    if(creatorp(this_player())){
        see_also = ({ "debug" , "showgrid",
                "wizvision", "godmode", "wizmap", "noclip" });
    }
    see_also += ({ "brief", "chancolors", "commandecho", "cursefilter",
            "terminal", "screen", "pk", "mute", "gag", "wimpy", "minimap",
            "annoyblock", "reprompt", "charmode", "keepalive", "timezone",
            "screenlock" });
    return ("用法: env\n\n"
            "显示一些基本的界面和游戏设置。\n" +
            "参考: "+implode(sort_array(see_also, 1), ", "));
}
