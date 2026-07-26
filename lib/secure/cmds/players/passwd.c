/*    /secure/cmds/players/passwd.c
 *    from the Dead Souls  Object Library
 *    passwd
 *    created by Descartes of Borg 951202
 */

#include <lib.h>
#include <flags.h>
#include <message_class.h>
#include "include/passwd.h"

inherit LIB_DAEMON;

mixed cmd(string args) {
    object ob;

    if( previous_object()->GetForced() )
        return "你不能被强制修改密码。";
    if( args && args != "" ) {
        if( !archp(previous_object()) )
            return "你不能修改其他玩家的密码。";
        if( !user_exists(args = convert_name(args)) )
            return "该用户不存在。";
        ob = find_player(args);
    }
    else ob = previous_object();
    previous_object()->eventPrint("正在为" +
            (ob ? ob->GetCapName() :
             capitalize(args)) + "在" +
            mud_name() + "上修改密码。", MSG_SYSTEM);
    if( previous_object() == ob ) {
        ob->eventPrint("旧密码：", MSG_PROMPT);
        input_to( (: OldPass :), I_NOECHO | I_NOESC, ob);
    }
    else  {
        previous_object()->eventPrint("新密码：", MSG_PROMPT);
        input_to( (: NewPass :), I_NOECHO | I_NOESC, ob || args);
    }
    return 1;
}

protected void OldPass(string pass, object who) {
    string oldpass;

    if( who != this_player() ) return;
    if( !pass || pass == "" ) {
        who->eventPrint("\n密码修改失败。", MSG_SYSTEM);
        return;
    }
    oldpass = this_player()->GetPassword();
    if( oldpass != crypt(pass, oldpass) ) {
        who->eventPrint("\n密码修改失败。", MSG_SYSTEM);
        return;
    }
    who->eventPrint("\n新密码：", MSG_PROMPT);
    input_to((: NewPass :), I_NOECHO | I_NOESC, who);
}

protected void NewPass(string pass, mixed who) {
    if( !pass || strlen(pass) < 5 ) {
        this_player()->eventPrint("密码至少需要5个字符，密码修改失败。",
                MSG_SYSTEM);
        return;
    }
    this_player()->eventPrint("\n确认新密码：", MSG_PROMPT);
    input_to( (: ConfirmPass :), I_NOECHO | I_NOESC, who, pass);
}

protected void ConfirmPass(string str, mixed who, string newpass) {
    if( str != newpass ) {
        this_player()->eventPrint("两次输入的密码不一致。", MSG_SYSTEM);
        return;
    }
    if( objectp(who) ) who->SetPassword(crypt(newpass, 0));
    else {
        string *lines;

        who = player_save_file(who);
        lines = explode(unguarded((: read_file, who :)),"\n");
        unguarded((: rm, who :));
        foreach(string line in lines) {
            string val;

            if( sscanf(line, "Password %s", val) )
                line = "Password \"" + crypt(newpass, 0) + "\"";
            unguarded((: write_file, who, line + "\n" :));
        }
    }
    this_player()->eventPrint("\n密码已修改。", MSG_SYSTEM);
}

string GetHelp(){
    int i;
    string ret = "命令格式：passwd\n";
    if(i = (archp(this_player()))) ret += "        passwd <玩家>\n";
    ret += "\n此命令允许你修改自己的密码";
    if(i) ret += "或指定玩家的密码";
    ret += "。\n参见：chfn";
    return ret;
}
