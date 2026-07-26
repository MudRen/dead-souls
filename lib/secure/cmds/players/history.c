/*    /secure/cmds/players/history.c
 *    from the Dead Souls Object Library
 *    command to view history information
 *    created by Descartes of Borg 960511
 */

#include <lib.h>
#include <message_class.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    int x;
    object player = this_player();
    if(!player) return 0;
    if(player->GetForced()) return 0;

    if( x = to_int(args) ) {
        if( previous_object()->SetHistorySize(x) != x ) {
            if( x < MIN_HISTORY_SIZE )
                return "历史记录大小至少为 " + MIN_HISTORY_SIZE + "。";
            else if( x > MAX_HISTORY_SIZE )
                return "历史记录大小不能超过 " + MAX_HISTORY_SIZE + "。";
            else return "无效的历史记录大小。";
        }
        else {
            previous_object()->eventPrint("历史记录大小已设置为：" + x);
        }
    }
    else {
        string* arr, tmp = ({});
        mapping history;
        int cmd_num, i;

        history = this_player()->GetCommandHist();
        cmd_num = sizeof(history);
        foreach(mixed key, mixed cmd in history) {
            if( !cmd ) continue;
            tmp += ({ sprintf("%:-5d %s", key, cmd) });
        }
        previous_object()->eventPage(tmp, MSG_SYSTEM);
    }
    return 1;
}

string GetHelp(string str) {
    return ("命令格式：history\n"
            "        history <大小>\n\n"
            "此命令让你查看命令历史记录。系统会记录你输入的命令，"
            "方便你快速执行或修改之前的命令。"
            "命令缓冲区的默认大小为" + MIN_HISTORY_SIZE + "，"
            "但你可以扩展到" + MAX_HISTORY_SIZE + "。"
            "你可以通过传递大小参数来更改历史缓冲区的大小。"
            "不带参数时，命令会显示历史缓冲区中的命令。\n\n"
            "以下是访问之前命令的语法：\n"
            "\t!!\t\t执行上一条命令\n"
            "\t!#\t\t执行第#条命令\n"
            "\t!-#\t\t执行之前第#条命令\n"
            "\t^old^new\t在上一条命令中将'old'替换为'new'并执行\n"
            "\t!#^old^new\t同上，但针对第#条命令\n"
            "\t!#s/old/new/g\t同上，但替换所有出现的'old'\n\n"
            "参见：alias, nickname");
}
