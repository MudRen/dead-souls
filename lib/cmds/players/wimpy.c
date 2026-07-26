/*    /cmds/players/wimpy.c
 *    from the Dead Souls Mud Library
 *    wimpy NUM
 *    wimpy STR
 *    created by Descartes of Borg 960113
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    int percentage;
    string cmd;

    if( !args || args == "" ) {
        percentage = this_player()->GetWimpy();
        cmd = this_player()->GetWimpyCommand();
        if( !percentage )
            this_player()->eventPrint("逃跑功能已关闭。", MSG_SYSTEM);
        else this_player()->eventPrint("百分比: " + percentage + "%\n"
                "命令: " + cmd, MSG_SYSTEM);
        return 1;
    }
    if( args == "0" ) {
        percentage = 0;
        cmd = 0;
    }
    else if( percentage = to_int(args) ) cmd = 0;
    else if( args == "on" ) {
        percentage = 23;
        cmd = 0;
    }
    else if( args == "off" ) {
        percentage = 0;
        cmd = 0;
    }
    else {
        percentage = 0;
        cmd = args;
    }
    if( !cmd ) {
        if( !percentage ) {
            this_player()->SetWimpy(0);
            this_player()->eventPrint("逃跑功能已关闭！你真勇敢！",
                    MSG_SYSTEM);
            return 1;
        }
        if( percentage > 30 ) {
            this_player()->eventPrint("逃跑阈值不能超过30%。",
                    MSG_SYSTEM);
            return 1;
        }
        else if( percentage < 1 ) return "这不是有效的百分比！";
        this_player()->SetWimpy(percentage);
        if( percentage > 20 ) {
            this_player()->eventPrint("真是个胆小鬼！拿出点勇气来！",
                    MSG_SYSTEM);
            return 1;
        }
        else if( percentage > 10 ) {
            this_player()->eventPrint("你很谨慎！", MSG_SYSTEM);
            return 1;
        }
        else {
            this_player()->eventPrint("你很勇敢，但不愚蠢！", MSG_SYSTEM);
            return 1;
        }
    }
    this_player()->SetWimpyCommand(cmd);
    this_player()->eventPrint("下次逃跑时你将执行命令: \"" + cmd +
            "\"。", MSG_SYSTEM);
    return 1;
}

string GetHelp(){
    return ("用法: wimpy [on | off | 百分比 | 命令]\n\n"
            "逃跑系统允许你在生命值低于最大生命值的一定百分比时"
            "自动执行命令。wimpy 命令允许你设置在哪个百分比时"
            "使用哪个命令。\"on\"和\"off\"参数分别快速设置为"
            "23%和0%。逃跑阈值不能超过30%。\n"
            "如果你设置了移动命令，例如：\n"
            "\tgo west\n"
            "逃跑系统会先尝试使用该命令，如果失败，它会寻找房间"
            "中的出口离开。但如果你设置的是其他命令（不是移动"
            "或进入命令），它不会尝试执行其他命令。\n"
            "例如，如果你输入命令：\n"
            "\twimpy gate to Mystery Person\n"
            "那么\"gate to Mystery Person\"就是你的逃跑命令，"
            "逃跑系统会在你逃跑时尝试执行该命令，不会尝试其他"
            "命令，即使传送失败（魔法值太低、目标不在线等）。\n"
            "不带参数时，wimpy 命令显示当前设置。\n"
            "参考: attack, status");
}

