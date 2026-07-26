/*    /secure/cmds/player/chfn.c
 *    from the Foundation II LPC Library
 *    just when you thought you were safe from lisp
 *    created by Descartes of Borg 950517
 */

#include <lib.h>

inherit LIB_DAEMON;

mixed cmd(string args) {
    function f;
    string rname;

    message("system", "正在为" +
            previous_object()->GetCapName() + "修改用户信息：", previous_object());
    rname = previous_object()->GetRealName();
    message("prompt", "真实姓名 [" + rname + "] ", previous_object());
    f = function(string str, string old, object ob) {
        function g;

        if( !str || str == "" ) str = old;
        if( str != old ) {
            ob->SetRealName(str);
            message("system", "真实姓名已更改为 " + str, ob);
        }
        else message("system", "真实姓名未更改。", ob);
        str = ob->GetEmail();
        message("prompt", "电子邮箱（在前面加#表示仅管理员可见）["
                + str + "] ", ob);
        g = function(string str, string old, object ob) {
            function h;

            if( !str || str == "" ) str = old;
            if( str != old ) {
                string a, b;

                if( sscanf(str, "%s@%s", a, b) != 2 ) {
                    message("system", "无效的电子邮箱。", ob);
                    return;
                }
                ob->SetEmail(str);
                message("system", "电子邮箱已更改为 " + str, ob);
            }
            else message("system", "电子邮箱未更改。", ob);
            str = (ob->GetWebPage() || "");
            message("prompt", "个人主页 [" + str + "]：", ob);
            h = function(string str, object who) {
                if( str == "" ) {
                    str = 0;
                }
                else if( str ) {
                    if( strlen(str) < 5 ) {
                        str = "http://" + str;
                    }
                    else {
                        if( str[0..3] != "http" ) {
                            str = "http://" + str;
                        }
                    }
                }
                if( !str ) {
                    message("system", "个人主页未更改。", who);
                }
                else {
                    who->SetWebPage(str);
                    message("system", "个人主页已更改。", who);
                    this_player()->save_player(this_player()->GetKeyName());
                    update("/secure/daemon/finger");
                }
            };
            input_to(h, 0, ob);
            this_player()->save_player(this_player()->GetKeyName());
            update("/secure/daemon/finger");
        };
        input_to(g, 0, str, ob);
        this_player()->save_player(this_player()->GetKeyName());
        update("/secure/daemon/finger");
    };
    input_to(f, "" + rname, previous_object());
    this_player()->save_player(this_player()->GetKeyName());
    update("/secure/daemon/finger");
    return 1;
}

string GetHelp(){
    return ("命令格式：chfn\n\n"
            "允许你修改你的finger信息。\n"
            "参见：passwd, finger");
}
