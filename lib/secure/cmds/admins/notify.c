/*  /cmds/secure/admin/notify
 *  from the Dead Souls Mud Library
 *  created by Blitz@Dead Souls 950115
 */

#include <lib.h>
#include <daemons.h>


varargs private void eventNotify(object who, string text);

mixed cmd(string str) {
    object ob = previous_object();
    string who;

    if(!archp(previous_object())) return 0;
    if( !ob ) return 0;
    who = ob->GetKeyName();
    if( sizeof(str) ) {
        eventNotify(ob, str);
        return 1;
    }
    ob->eventPrint("[ Dead Souls 通知系统 ]");
    ob->eventPrint("请编写你的通知消息。\n");
    ob->eventEdit(DIR_TMP + "/" +who+ ".notice", (: eventNotify, ob, 0 :));
    return 1;
}

varargs private void eventNotify(object who, string text) {
    int x;
    string file, str;
    if( !who ) return;
    if( !text ) {
        string * lines;
        file = DIR_TMP + "/" +who->GetKeyName() + ".notice";
        if( file_size(file) < 1 ) return;
        str = read_file(file);
        str = implode(filter(lines = explode(str, "\n"), (: sizeof :)), "\n");
        rm(file);
    } else str = text;
    if( !sizeof(str) ) return;
    x = NOTIFY_D->eventAddNotice(who, str);
    if( x )
        who->eventPrint("你的通知 [编号 #"+(x-1)+"] 已发布！");
    else
        who->eventPrint("添加通知时出错。");
}

string GetHelp(){
    return ("语法: notify\n"
            "        notify <消息内容>\n\n"
            "此命令允许具有相应权限的用户将消息添加到通知数据库中。"
            "所有新通知会在任何创造者登录时显示。"
            "单独输入 \"notify\" 会进入文本编辑器。"
            "否则将使用传入的消息。");
}
