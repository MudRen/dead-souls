/*  /cmds/creators/notices
 *  from the Dead Souls Mud Library
 *  created by Blitz@Dead Souls 950115
 */

#include <lib.h>
#include <daemons.h>

#define OneDay  (3600 * 24)

string GetHelp(string foo);

mixed cmd(string str) {
    string * words;
    object ob = this_player();
    int x;
    if( !sizeof(str) ) x = 1;
    else x = to_int(str);
    if( x < 1 ) {
        if( !archp(this_player()) ) return GetHelp(0);
        words = explode(str, " ");
        if( words[0] == "-d" ) {
            if( sizeof(words) < 2 ) return GetHelp(0);
            x = to_int(words[1]);
            if( x < 1 && words[1] != "0" )
                return "无效值（"+words[1]+"）。";
            if( NOTIFY_D->eventRemoveNotice(x) )
                ob->eventPrint("通知编号 " + x + " 已被删除。");
            else ob->eventPrint("无法删除编号 " + x + "。");
            return 1;
        }
        else if( words[0] == "-p" && sizeof(words) > 1 ) {
            string file = words[1];
            if( sizeof(words) > 2 ) x = to_int(words[2]);
            else x = 1;
            if( x < 1 ) return GetHelp(0);
            if( NOTIFY_D->eventWriteNotices(file, time() - (OneDay*x)) )
                ob->eventPrint("通知已导出到 " + file + "。");
            else ob->eventPrint("未找到通知，未执行任何操作。");
            return 1;
        }
        else return GetHelp(0);
    }
    x = time() - (OneDay * x);
    if( !NOTIFY_D->eventPrintNotices(this_player(), x) )
        return "没有找到最近的通知。";
    else return 1;
}

string GetHelp(string foo) {
    string str;
    str = "语法：notices [回溯天数]\n\n"
        "不带参数时，此命令显示过去24小时内发布的所有通知。"
        "你也可以指定回溯多少天进行搜索。例如，"
        "\"notices 7\" 将显示过去一周内发布的所有通知。";
    if( archp(this_player()) )
        str += "\n管理员命令：notices -d <编号>\n"
            "               notices -p <文件名> <回溯天数>\n\n"
            "d 选项删除指定的通知编号。\n"
            "p 选项将输出导出到<文件名>";
    return str;
}
