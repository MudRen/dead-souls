#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    mixed tmp;
    string stat;
    int amt;

    if( !args || args == "" ) {
        amt = this_player()->GetCustomDeviations();
        this_player()->eventPrint("你还有 " + amt + " 点偏差点数可以使用。", MSG_SYSTEM);
        return 1;
    }
    if(args == "enable"){
        int i = this_player()->GetDeviating();
        if(i){
            write("你已经启用了偏差功能。");
            return 1;
        }
        i = this_player()->SetDeviating(1);
        if(i) write("偏差功能已启用。");
        else write("偏差功能未启用。请联系管理员寻求帮助。");
        return 1;
    }
    if(!this_player()->GetDeviating()){
        write("你还没有启用偏差功能。");
        write("请输入: help deviate");
        write("以及: help deviation");
        return 1;
    }
    amt = to_int((tmp = explode(args, " "))[<1]);
    if( sizeof(tmp) == 1 ) return "偏差哪个属性多少点？";
    stat = implode(tmp[0..<2], " ");
    tmp = this_player()->eventDeviateStat(stat, amt);
    if( stringp(tmp) ) return tmp;
    if( !tmp ) return "偏差失败。";
    this_player()->eventPrint("你的 " + stat + " 等级现在是 " + tmp +
            "，还有 " +
            this_player()->GetCustomDeviations() +
            " 点偏差点数。", MSG_SYSTEM);
    return 1;
}

string GetHelp(){
    return ("用法: deviate\n"
            "        deviate enable\n"
            "        deviate 属性 数量\n\n"
            "改变指定属性的\"属性等级\"，"
            "使其在玩家升级时更频繁地提升。"
            "但这会带来巨大的经验值惩罚。"
            "偏差操作和惩罚都是不可逆的。"
            "在继续之前，请阅读偏差帮助文件：\nhelp deviation\n\n"
            "如果你决定使用偏差，请先输入以下命令启用：\n"
            "deviate enable\n参考: deviation, customize, "
            "stat, stats, score");
}
