#include <lib.h>
#include <dirs.h>
#include <flags.h>
#include <message_class.h>

inherit LIB_DAEMON;

protected void NewPass(string pass);
protected void ConfirmPass(string str, string newpass);

string savefile;

mixed cmd(string args) {

    if(!archp(previous_object())) {
        write("No.");
        return 1;
    }

    if(!args || !sizeof(args)) args = "me";

    args = lower_case(args);

    if(args == "me" || args == this_player()->GetKeyName()){
        write("要重置您自己的密码，请使用命令：passwd");
        return 1;
    }

    if( previous_object()->GetForced() )
        return "您不能被强制更改密码。";
    if( previous_object() != this_player() )
        return "您正在被利用来重置他人的密码。";

    if(!user_exists(args)){
        write("此MUD上不存在该用户。");
        return 1;
    }

    if(find_player(args)){
        write("该玩家当前已登录。请使用 "
                "passwd 命令重置其密码。");
        return 1;
    }

    savefile = save_file(DIR_CRES + "/" + args[0..0] + "/" + args);
    if(!file_exists(savefile)){
        write("找不到 "+savefile+"。正在查找备选文件。");
        savefile = save_file(DIR_PLAYERS + "/" + args[0..0] + "/"+ args);
    }

    if(!file_exists(savefile)){
        write("找不到存档文件。退出。");
        return 1;
    }

    write("已找到 "+savefile+"。");

    previous_object()->eventPrint("新密码：", MSG_PROMPT);
    input_to( (: NewPass :), I_NOECHO | I_NOESC, previous_object() || args);
    return 1;
}

protected void NewPass(string pass) {
    if( !pass || strlen(pass) < 5 ) {
        this_player()->eventPrint("密码长度必须至少为5个字符，密码更改失败。",
                MSG_SYSTEM);
        return;
    }
    this_player()->eventPrint("\n确认：", MSG_PROMPT);
    input_to( (: ConfirmPass :), I_NOECHO | I_NOESC, pass);
}

protected void ConfirmPass(string str, string newpass) {
    string *lines;
    if( str != newpass ) {
        this_player()->eventPrint("密码不匹配。", MSG_SYSTEM);
        return;
    }

    lines = explode(unguarded((: read_file, savefile :)),"\n");
    unguarded((: rm, savefile :));
    foreach(string line in lines) {
        string val;

        if( sscanf(line, "Password %s", val) )
            line = "Password \"" + crypt(newpass, 0) + "\"";
        unguarded((: write_file, savefile, line + "\n" :));
    }
    this_player()->eventPrint("\n密码已更改。", MSG_SYSTEM);
}

string GetHelp() {
    return ("语法：resetpasswd <玩家>\n\n"
            "允许您在某人未登录时更改其密码。\n"
            "另见：passwd");
}
