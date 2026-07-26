/*    /cmds/players/customize.c
 *    from the Dead Souls Mud Library
 *    customize
 *    customize STAT AMOUNT
 *    created by Descartes of Borg 950113
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    mixed tmp;
    string stat;
    int amt;

    if( !args || args == "" ) {
        amt = this_player()->GetCustomStats();
        this_player()->eventPrint("你还有 " + amt + " 点可以分配给属性。", MSG_SYSTEM);
        return 1;
    }
    amt = to_int((tmp = explode(args, " "))[<1]);
    if( sizeof(tmp) == 1 ) return "定制哪个属性多少点？";
    stat = implode(tmp[0..<2], " ");
    tmp = this_player()->eventCustomizeStat(stat, amt);
    if( stringp(tmp) ) return tmp;
    if( !tmp ) return "提升属性失败。";
    this_player()->eventPrint("你的 " + stat + " 现在是 " + tmp +
            "，还有 " +
            this_player()->GetCustomStats() +
            " 点可以分配。", MSG_SYSTEM);
    return 1;
}

string GetHelp(){
    return ("用法: customize [属性 数量]\n\n"
            "允许你使用定制点数来提升你的初始属性。"
            "不带参数使用此命令可以查看剩余可用点数。\n"
            "示例: customize strength 5"
            "\n注意: 点数一旦使用就无法恢复。你不会获得额外的定制点数。\n"
            "参考: stats, stat, skills, deviation");
}
