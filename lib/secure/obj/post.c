/*    /lib/obj/post.c
 *    from Foundation II
 *    the user front end to the IIPS version 3.1
 *    created by Descartes of Borg 940509
 */

#include <lib.h>
#include <daemons.h>
#include <iips.h>
#include "include/post.h"

inherit LIB_ITEM;

nosave private int __Screen, __Lines, __NumLetters;
nosave private int __Begin,__Current,__CommandLine,__FromMenu,__IncomingFlag;
nosave private string __Folder, __Owner, __CurrentMenu;
nosave private mapping __Options, __TmpPost, __ChangedOptions;
nosave private int *__Delete;
nosave private string *__FwdRply;
nosave private mapping *__BoxInfo, *__PostalOptions;

void create() {
    item::create();
    SetKeyName("post box");
    SetId( ({ "post box", "box", POSTAL_ID }) );
    SetAdjectives( ({ "post", "a", "imaginary" }) );
    SetShort("邮箱");
    SetLong("一个邮箱。");
    SetProperty("no steal", 1);
    SetInvis(1);
    SetMass(0);
    SetValue(0);
    SetPreventGet( (: Destruct :) );
    SetPreventDrop( (: Destruct :) );
    SetPreventPut( (: Destruct :) );
    __PostalOptions = ({
            ([ "key":"askcc", "value":({"N","Y"}), "desc":"发送邮件时提示输入抄送：" ]),
            (["key":"quit", "value":({"N","Y"}), "desc":"退出邮件时确认："]),
            (["key":"metoo", "value":({"N","Y"}),"desc":"别名中包含自己时也发送给自己："]),
            (["key":"delete", "value":({"N","Y"}), "desc":"删除信件时确认："]),
            (["key":"notify", "value":({"N","Y"}), "desc":"收到新邮件时通知："]),
            ([ "key":"message", "value":"$N 发来了新邮件\n"
             "主题：$S", "desc":"收到新邮件时的通知消息：" ]),
            ([ "key": "content", "value":({"message only", "header and message"}),
             "desc":"阅读信件时显示的内容：" ]),
            ([ "key":"forward", "value":"none", "desc":"转发 incoming 邮件的地址：" ]),
            ([ "key":"sig file", "value":"none", "desc":"签名文件：" ]),
            ([ "key":"commands", "value":({"N","Y"}), "desc":"菜单中隐藏命令列表：" ]),
            ([ "key":"read", "value":({"N","Y"}), "desc":"设为当前信件时自动阅读：" ])
    });
}

string tmpmail(){
    mixed tmpmaildir = homedir(this_player());
    if(!tmpmaildir || !directory_exists(tmpmaildir)) return "/tmp/"+this_player()->GetKeyName();
    else return tmpmaildir+"/tmp/mail.tmp";
}

void init() {
    item::init();
    if(this_player() != environment(this_object())) {
        this_object()->eventDestruct();
        return;
    }
    __Options = OPTIONS_D->query_options(__Owner =
            this_player()->GetKeyName());
    if(!(__Lines = to_int(this_player()->GetEnvVar("LINES"))))
        __Lines = 24;
    if(!(__Screen = to_int(this_player()->GetEnvVar("SCREEN"))))
        __Screen = 80;
    if((__NumLetters = __Lines - 10) < 0) __NumLetters = 5;
}

private void restore_box(string folder) {
    int x;

    if(!pointerp(__BoxInfo=FOLDERS_D->query_box_info(__Owner, folder)))
        __BoxInfo = ({});
    __Folder = folder;
    __TmpPost = ([]);
    __Delete = allocate(x = sizeof(__BoxInfo));
    if(!x) __Current = -1;
    else __Current = 0;
    __Begin = 0;
}

private void save_box() {
    FOLDERS_D->delete_posts(__Owner, __Folder, __Delete);
}

private void destruct_box(string str) {
    message("mail", str, this_player());
    this_object()->eventDestruct();
}

private int valid_folder(string str) {
    int i;

    if(str == "" || !str) return 0;
    if(str[0] != '=' && str != "new") return 0;
    i = strlen(str = lower_case(str));
    while(i-- > 1) if(str[i] < 'a' || str[i] > 'z') return 0;
    return 1;
}

private int set_current(mixed val) {
    int i;

    if(intp(val)) __Current = val;
    else {
        i = sizeof(__BoxInfo);
        while(i--) {
            if(__BoxInfo[i]["id"] == val) {
                __Current = i;
                break;
            }
        }
    }
    if(__Current < __Begin) __Begin = __Current;
    else if(__Current >= __Begin+10) __Begin = __Current-9;
    return __Current;
}

void start_post(string str) {
    string *args;
    int i, maxi;;

    if(str && str != "") {
        maxi = sizeof(args = explode(str, ","));
        if(args[0][0] == '-' && strlen(args[0]) == 2) {
            switch(args[0][1]) {
                case 'r':
                    restore_box("new");
                    index_cmd("");
                    return;
                case 'f':
                    if(maxi < 2) {
                        message("mail", "没有该文件夹。", this_player());
                        this_object()->eventDestruct();
                        return;
                    }
                    else if(maxi>2 || (!valid_folder(args[1]) &&
                                args[1] != "new")) {
                        message("mail", "文件夹名无效。", this_player());
                        this_object()->eventDestruct();
                        return;
                    }
                    else {
                        restore_box(args[1]);
                        indices(0);
                        return;
                    }
                case 'a':
                    __CommandLine = 1;
                    if(maxi < 2) index_cmd("a");
                    else index_cmd(implode(args[1..maxi-1], " "));
                    return;
            }
        }
        __CommandLine = 1;
        __TmpPost = ([]);
        __FwdRply = 0;
        send_letter(args);
        return;
    }
    restore_box("new");
    indices(0);
}

private void primary_prompt() {
    message("prompt", "\n命令：\n", this_player());
}

private void secondary_prompt() {
    message("prompt", sprintf("\n命令（%s 返回%s菜单）：\n",
                __CurrentMenu[0..0],  __CurrentMenu),
            this_player());
}

varargs nosave private void postal_error(string str, string ind, mixed args) {
    message("mail", sprintf("\n%%^RED%%^%s\n", str), this_player());
    primary_prompt();
    if(args) input_to(sprintf("%s_cmd", (ind ? ind : __CurrentMenu)), args);
    else input_to(sprintf("%s_cmd", (ind ? ind : __CurrentMenu)));
}

varargs nosave private void postal_success(string str,string ind,mixed args) {
    message("mail", sprintf("\n%%^GREEN%%^%s\n", str), this_player());
    secondary_prompt();
    if(args) input_to(sprintf("%s_cmd", (ind ? ind : __CurrentMenu)), args);
    else input_to(sprintf("%s_cmd", (ind ? ind : __CurrentMenu)));
}

varargs protected void indices(int x, string str) {
    int i, maxi;

    __CurrentMenu = "index";
    if(str && str != "") {
        index_cmd(str);
        return;
    }
    __Begin = x;
    __FromMenu = 1;
    message("mail", "\n%^INITTERM%^星际邮政服务 "
            "(IIPS) 3.1     Descartes of Borg 1993, 1994", this_player());
    message("mail", sprintf("\n%%^CYAN%%^%s", center(sprintf("当前文件夹：%s，共 %s",
                        __Folder,consolidate(maxi=sizeof(__BoxInfo),"封信\n")),
                    __Screen)), this_player());
    if(!maxi) __Current = -1;
    else for(i=x; i<maxi && i < x+__NumLetters; i++)
        message("mail", sprintf("%s%s) %s %s %s %s %s\n",
                (__Current == i ? "%^YELLOW%^BOLD%^*" : " "),
                ((i+1 > 99) ? (""+(i+1)) : ((i+1 > 9) ? (" "+(i+1)) : ("  "+(i+1)))),
                (__BoxInfo[i]["read"] ? " " : "N"),
                (__Delete[i] ? "D" : " "),
                arrange_string(capitalize(__BoxInfo[i]["from"]), 30),
                arrange_string(postal_time(__BoxInfo[i]["date"]), 7),
                arrange_string(__BoxInfo[i]["subject"], __Screen-40)), this_player());
    index_menu();
}

varargs protected void aliases(string str) {
    __CurrentMenu = "alias";
    if(str && str != "") {
        alias_cmd(str);
        return;
    }
    message("mail", "\n%^INITTERM%^星际邮政服务 "
            "(IIPS) 3.1     Descartes of Borg 1993, 1994", this_player());
    message("mail", sprintf("\n%%^CYAN%%^%s", center(sprintf("%s 群组与"
                        "个人别名菜单", mud_name()))), this_player());
    message("mail", sprintf("\n%s\n",
                format_page(keys(OPTIONS_D->query_groups(__Owner) +
                        LOCALPOST_D->query_mud_groups()),__Screen/20)),this_player());
    alias_menu();
}

varargs protected void options(string str) {
    string tmp;
    int i, maxi;

    __CurrentMenu = "option";
    if(str && str != "") {
        option_cmd(str);
        return;
    }
    message("mail", "\n%^INITTERM%^星际邮政服务 "
            "(IIPS) 3.1     Descartes of Borg 1993, 1994", this_player());
    message("mail", sprintf("\n%%^CYAN%%^%s", center("IIPS 3.1 选项菜单\n",
                    __Screen)), this_player());
    maxi = sizeof(__PostalOptions);
    for(i=0; i<maxi; i++) {
        if(pointerp(__PostalOptions[i]["value"]))
            tmp = __PostalOptions[i]["value"][__Options[__PostalOptions[i]["key"]]];
        else if(!(tmp = __Options[__PostalOptions[i]["key"]]))
            tmp = __PostalOptions[i]["value"];
        message("mail", sprintf("%s) %-45s %s\n", (i+1>9) ? (i+1)+"" :" "+(i+1),
                __PostalOptions[i]["desc"], tmp),
            this_player());
    }
    option_menu();
}

nosave private void help(string arg, string ind) {
    if(!ind) ind = __CurrentMenu;
    if(arg && arg != "") {
        help_cmd(arg, ind);
        return;
    }
    message("mail", "\n%^INITTERM%^星际邮政服务 "
            "(IIPS) 3.1     Descartes of Borg 1993, 1994", this_player());
    message("mail",sprintf("\n%%^CYAN%%^%s\n",center("IIPS 3.1 帮助菜单",
                    __Screen)), this_player());
    help_menu(ind);
}

private void index_menu() {
    if(__Options["commands"]) {
        primary_prompt();
        input_to("index_cmd");
        return;
    }
    message("mail", "\n"+center("a)别名菜单, c)切换文件夹, d)删除, "
        "f)转发, h)帮助, m)写信,", __Screen), this_player());
    message("mail", center("n)下一封, o)选项菜单, p)上一封, q)退出, Q)不保存退出,", __Screen), this_player());
    message("mail", center("s)保存到文件夹, S)保存到文件, "
        "u)取消删除", __Screen), this_player());
    message("mail", center("按<回车>阅读当前信件\n", __Screen),
            this_player());
    primary_prompt();
    input_to("index_cmd");
}

private void alias_menu() {
    if(__Options["commands"]) {
        primary_prompt();
        input_to("alias_cmd");
        return;
    }
    message("mail", center("d)从别名中删除, e)添加到别名, "
        "h)帮助, i)索引菜单, ", __Screen), this_player());
    message("mail", center("l)列出别名, m)创建别名, o)选项菜单, "
        "q)退出, Q)不保存退出, ", __Screen), this_player());
    message("mail", center("r)删除别名\n", __Screen),this_player());
    primary_prompt();
    input_to("alias_cmd");
}

private void option_menu() {
    if(__Options["commands"]) {
        primary_prompt();
        input_to("option_cmd");
        return;
    }
    message("mail", "\n"+center("输入选项编号进行修改。", __Screen), this_player());
    message("mail", center("a)别名菜单, h)帮助, i)索引菜单, "
        "q)退出, Q)不保存退出,", __Screen), this_player());
    message("mail", center("s)保存选项更改\n", __Screen), this_player());
    primary_prompt();
    input_to("option_cmd");
}

private void help_menu(string ind) {
    int i, maxi;

    message("help", "\n\n\t输入以下选项进入其他菜单：", this_player());
    message("help", center("a)别名菜单, i)索引菜单, o)选项菜单",
        __Screen), this_player());
    message("help", "\n\t或输入以下选项查看详细帮助：",
            this_player());
    switch(ind) {
        case "index":
            message("help", center("c)切换文件夹, d)删除, f)转发, "
                "m)写信, n)下一封,", __Screen), this_player());
            message("help", center("p)上一封, q)退出, "
                "Q)不保存退出, r)回复,", __Screen), this_player());
            message("help", center("s)保存到文件夹, S)保存到文件,",
                __Screen), this_player());
            message("help", center("x)其他菜单帮助, y)IIPS 详细用户手册\n", __Screen), this_player());
            break;
        case "alias":
            message("help", center("d)从别名中删除, e)添加到别名, "
                "m)创建别名, q)退出,", __Screen), this_player());
            message("help", center("Q)不保存退出, r)删除别名,", __Screen), this_player());
            message("help", center("x)其他菜单帮助, y)IIPS 详细用户手册\n", __Screen), this_player());
            break;
        case "option":
            for(i=0, maxi = sizeof(__PostalOptions); i<maxi;i++)
                message("help", center(sprintf("%d) %s", (i+1),
                            __PostalOptions[i]["desc"]), __Screen), this_player());
            message("help", sprintf("\n%s",center("另有：q)退出, Q)不保存退出, "
                    "s)保存选项更改,", __Screen)), this_player());
            message("help", center("x)其他菜单帮助, y)IIPS 详细用户手册\n", __Screen), this_player());
            break;
        default:
            postal_error("无效的邮政菜单。");
            return;
    }
    primary_prompt();
    input_to("help_cmd", ind);
}

protected void index_cmd(string str) {
    string cmd, args;
    string *tmp;
    int x;

    __CurrentMenu = "index";
    if(__IncomingFlag) {
        __IncomingFlag = 0;
        postal_error("新邮件已到达！\n命令已忽略。");
        return;
    }
    if(str == "" || !str) {
        if(__Current < 0 || __Current >= sizeof(__BoxInfo)) {
            postal_error("未设置当前信件。");
            return;
        }
        if(__FromMenu) read_letter(__Current);
        else if(set_current(__Current+1) < sizeof(__BoxInfo))
            read_letter(__Current);
        else read_letter(set_current(__Current - 1));
        return;
    }
    if(sscanf(str, "%d", x) && x) {
        if(x>0 && x <= sizeof(__BoxInfo)) {
            if(__Options["read"]) read_letter(set_current(x-1));
            else {
                set_current(x-1);
                indices(__Begin);
            }
        }
        else postal_error("信件编号无效。");
        return;
    }
    if(!sizeof(tmp = explode(str, " "))) cmd = "";
    else cmd = tmp[0][0..0];
    if(sizeof(tmp) > 1) args = implode(tmp = tmp[1..sizeof(tmp)-1], " ");
    else {
        args = "";
        tmp = ({});
    }
    switch(cmd) {
        case "a": aliases(args); return;
        case "c": change_folder(args); return;
        case "d": case "u": delete_letter(cmd, args); return;
        case "f": forward_letter(args, 0); return;
        case "h": help(args, "index"); return;
        case "i":
                  indices(__Current < __Begin+__NumLetters ? __Begin :
                          __Current-(__NumLetters-1), args);
                  return;
        case "m":
                  __FwdRply = 0;
                  __TmpPost = ([]);
                  send_letter(tmp);
                  return;
        case "n": index_cmd(""+(__Current+2)); return;
        case "o": options(args); return;
        case "p": index_cmd(""+(__Current)); return;
        case "q": case "Q": quit_box(cmd); return;
        case "r": reply(args); return;
        case "s": case "S": save_letter(cmd, args); return;
        default:
                            postal_error("无效的邮政命令。");
                            return;
    }
}

protected void alias_cmd(string str) {
    string cmd, args;
    string *tmp;

    __CurrentMenu = "alias";
    if(str == "" || !str) {
        if(__CommandLine) destruct_box("无效的别名命令。");
        else postal_error("无效的别名命令。");
        return;
    }
    cmd = (tmp = explode(str, " "))[0][0..0];
    if(sizeof(tmp) > 1) args = implode(tmp[1..sizeof(tmp)-1], " ");
    else args = "";
    switch(cmd) {
        case "a": aliases(args); return;
        case "d": case "e": alias_members(cmd, args); return;
        case "m": case "r": alias_creation(cmd, args); return;
        case "h": help(args, "alias"); return;
        case "i":
                  indices(__Current < __Begin+__NumLetters ? __Begin :
                          __Current-(__NumLetters-1), args);
                  return;
        case "l": list_alias(args); return;
        case "o": options(args); return;
        case "q": case "Q": quit_box(cmd); return;
        case "s": aliases(args); return;
        default: alias_cmd(0); return;
    }
}

protected void option_cmd(string str) {
    string cmd, args;
    string *tmp;
    int x;

    __CurrentMenu = "option";
    if(str == "" || !str) {
        postal_error("无效的选项命令。");
        return;
    }
    if(sscanf(str, "%d", x) && x) {
        change_option(x-1);
        return;
    }
    cmd = (tmp = explode(str, " "))[0][0..0];
    if(sizeof(tmp) > 1) args = implode(tmp[1..sizeof(tmp)-1], " ");
    else args = "";
    switch(cmd) {
        case "a": aliases(args); return;
        case "h": help(args, "option"); return;
        case "i":
                  indices(__Current < __Begin+__NumLetters ? __Begin :
                          __Current-(__NumLetters-1), args);
                  return;
        case "o": options(args); return;
        case "q": case "Q": quit_box(cmd); return;
        case "s": save_options(); return;
        default: option_cmd(0); return;
    }
}

protected void help_cmd(string str, string ind) {
    string tmp, file;      if(str == "" || !str) {
        postal_error("无效的帮助命令。", "help", ind);
        return;
    }
    switch(str = str[0..0]) {
        case "a": aliases(""); return;
        case "i": indices(__Begin); return;
        case "o": options(""); return;
        case "q": case "Q": file = "quitting"; break;
    }
    if(!(tmp = read_file(DIR_POSTAL_HELP+"/"+file))) tmp = "未找到。\n";
    this_player()->eventPage(explode(tmp, "\n"), "help", (: end_help :));
}

void end_help() {
    secondary_prompt();
    input_to("help_cmd");
}

private string postal_time(mixed val) {
    string *parts;
    string heure;
    int x;

    if(stringp(val) && x = to_int(val)) heure = ctime(time());
    else if(stringp(val)) heure = val;
    else heure = ctime(val);
    parts = explode(replace_string(heure, "  ", " "), " ");
    return sprintf("%s %s", parts[2], parts[1]);
}

private string header(mapping borg) {
    int x;

    return sprintf("%%^GREEN%%^%s%%^RESET%%^ 发来\n收件人：%s%s"
            "主题：%%^GREEN%%^%s",
            (stringp(borg["date"]) ? ((x=to_int(borg["date"])) ? ctime(x) :
                                      borg["date"]) : ctime(borg["date"])), capitalize(borg["from"]),
            wrap(implode(borg["to"], ",  "), __Screen),
            (sizeof(borg["cc"]) ? sprintf("Cc: %s",wrap(implode(borg["cc"], ",  "),
                                                        __Screen)) : ""), borg["subject"]);
}

protected void change_folder(string str) {
    if(str == "" || !str) {
        message("prompt", "切换到哪个文件夹？\n", this_player());
        input_to("get_folder");
        return;
    }
    if(!valid_folder(str)) {
        __FromMenu = 1;
        postal_error("文件夹名无效。");
        return;
    }
    if(!__Options["delete"] || member_array(1, __Delete) == -1)
        next_folder("", str);
    else {
        message("prompt", "删除标记的信件（默认'y'）？\n",
                this_player());
        input_to("next_folder", str);
    }
}

protected void next_folder(string str, string folder) {
    if(str == "" || !str) str = "y";
    else str = (lower_case(str)[0..0]);
    if(str == "y") save_box();
    else if(str != "n") {
        message("prompt", "无效命令。请输入 'y' 或 'n'：\n",this_player());
        input_to("next_folder");
    }
    restore_box(folder);
    indices(__Begin);
}

protected void get_folder(string str) {
    if(str == "" || !str) {
        __FromMenu = 1;
        postal_error("文件夹名无效。");
        return;
    }
    change_folder(str);
}

nosave private void delete_letter(string cmd, string args) {
    int x, i, from, to, maxi;

    if(args == "" || !args) {
        from = __Current;
        to = __Current;
    }
    else {
        sscanf(args, "%d-%d", from, to);
        if(!to) to = from-1;
        else to--;
        from--;
    }
    if(from > to || from < 0 || to >= sizeof(__BoxInfo)) {
        postal_error("信件范围无效。");
        return;
    }
    for(i= from; i < to+1; i++) {
        if(cmd == "u" && !__Delete[i]) {
            __FromMenu = 1;
            postal_error(sprintf("信件 %d 未标记为删除！",i+1));
        }
        else if(cmd == "d" && __Delete[i])
            postal_error(sprintf("信件 %d 已标记为删除！",i+1));
        else if(!__BoxInfo[i]["read"] && cmd == "d" &&
                !__Options["unread delete"]) {
            message("mail", sprintf("\n%%^RED%%^信件 %d 尚未阅读！",
                        i+1), this_player());
            message("prompt","仍然删除吗（默认 n）：\n",this_player());
            input_to("unread_delete", ({ i+1, to+1 }));
            return;
        }
        else __Delete[i] = (cmd == "u" ? 0 : 1);
    }
    if(cmd == "d" && (args == "" || !args)) {
        for(i=__Current, maxi = sizeof(__BoxInfo); i<maxi; i++) {
            if(!__Delete[i]) {
                set_current(i);
                if(!__FromMenu) {
                    read_letter(__Current);
                    return;
                }
                else {
                    indices(__Current < __Begin+__NumLetters ? __Begin :
                            __Current-(__NumLetters-1));
                    return;
                }
            }
        }
    }
    if(__FromMenu) {
        indices(__Current < __Begin+__NumLetters ? __Begin :
                __Current-(__NumLetters-1));
        return;
    }
    if(to == from) postal_success(sprintf("信件 %d %s",from+1,
                (cmd == "d" ? "已标记为删除" : "已取消删除")));
    else postal_error(sprintf("信件 %d 至 %d %s。",
                (from+1), (to+1), (cmd == "d" ? "已标记为删除" : "已取消删除")));
}

protected void unread_delete(string str, int *milk) {
    if(str == "" || !str) str = "y";
    else str = lower_case(str[0..0]);
    if(str == "y") __Delete[milk[0]-1] = 1;
    if(milk[0] < milk[1]) {
        delete_letter("d", milk[0]+"-"+milk[1]);
        return;
    }
    __FromMenu = 1;
    secondary_prompt();
    input_to("index_cmd");
}

private void quit_box(string cmd) {
    int i;

    if(__Options["quit"]) {
        message("prompt", "你真的想退出吗（默认'n'）？\n",
                this_player());
        input_to("confirm_quit", cmd);
        return;
    }
    really_quit(cmd);
}

private void really_quit(string cmd) {
    int i;

    if(cmd == "Q") {
        message("mail", "\n正在退出 IIPS，不保存删除操作。\n",
                this_player());
        this_object()->eventDestruct();
        return;
    }
    if(!__Options["delete"]) {
        save_box();
        message("mail", "\n正在退出 IIPS。\n", this_player());
        this_object()->eventDestruct();
        return;
    }
    i = sizeof(__Delete);
    while(i--) {
        if(__Delete[i]) {
            message("prompt", "删除标记的信件（默认'y'）？\n",
                    this_player());
            input_to("confirm_delete");
            return;
        }
    }
    message("mail", "\n正在退出 IIPS。\n",
            this_player());
    this_object()->eventDestruct();
}

protected void confirm_quit(string str, string cmd) {
    if(str == "" || !str) str = "n";
    else str = lower_case(str)[0..0];
    if(str == "y") {
        really_quit(cmd);
        return;
    }
    else if(str == "n") {
        indices(__Current < __Begin+__NumLetters ? __Begin :
                __Current - (__Lines-1));
        return;
    }
    message("prompt", "请输入 'y' 或 'n'：\n", this_player());
    input_to("confirm_quit", cmd);
}

protected void confirm_delete(string str) {
    if(str == "" || !str) str = "y";
    else str = lower_case(str)[0..0];
    if(str == "y") {
        save_box();
        message("mail", "\n正在退出 IIPS。\n", this_player());
        this_object()->eventDestruct();
        return;
    }
    else if(str == "n") {
        message("mail", "\n标记的信件将保留不删除。\n"
                "正在退出 IIPS。\n", this_player());
        this_object()->eventDestruct();
        return;
    }
    message("prompt", "请输入 'y' 或 'n'：\n", this_player());
    input_to("confirm_delete");
}

nosave private void save_letter(string cmd, string args) {
    string *tmp;
    string folder;
    int letter, i, maxi;

    if(args && args != "") {
        if(sizeof(tmp = explode(args, " ")) == 2) {
            if(!sscanf(tmp[0], "%d", letter) || !letter) {
                sscanf(tmp[1], "%d", letter);
                folder = tmp[0];
            }
            else folder = tmp[1];
        }
        else if(!sscanf(args, "%d", letter) || !letter) folder = args;
        else folder = args;
    }
    else {
        folder = 0;
        letter = 0;
    }
    if(!letter) letter = __Current;
    else letter--;
    if(!folder) {
        if(cmd == "S") message("prompt","保存到哪个文件？\n",this_player());
        else message("prompt", sprintf("保存到哪个文件夹（默认 %s）？\n",
                    sprintf("=%s", convert_name(__BoxInfo[letter]["from"]))),
                this_player());
        input_to("get_save_location", ({ letter, cmd }));
        return;
    }
    if(cmd == "s") {
        if(!valid_folder(folder)) {
            postal_error("文件夹名无效。");
            return;
        }
        FOLDERS_D->add_post(__Owner, folder, __BoxInfo[letter]);
        message("mail", "\n信件已保存。\n", this_player());
        set_current(letter);
        __Delete[__Current] = 1;
    }
    else if(cmd == "S") {
        folder = absolute_path(this_player()->get_path(), folder);
        if(!creatorp(this_player()) ||
                !(master()->valid_write(folder, this_player()))) {
            postal_error("访问被拒绝。");
            return;
        }
        write_file(folder,
                LETTERS_D->query_letter(__BoxInfo[letter]["id"]));
        message("mail", sprintf("信件已保存到 %s。\n", folder),
                this_player());
        set_current(letter);
        __Delete[__Current] = 1;
    }
    if(!__FromMenu)
        for(i=__Current, maxi = sizeof(__BoxInfo); i<maxi; i++) {
            if(!__Delete[i]) {
                read_letter(__Current);
                return;
            }
        }
    secondary_prompt();
    input_to("index_cmd");
}

protected void get_save_location(string str, mixed *vals) {
    if(str == "" || !str) {
        if(vals[1] == "s")
            str = sprintf("=%s", convert_name(__BoxInfo[vals[0]]["from"]));
        else {
            postal_error("文件名无效。");
            return;
        }
    }
    save_letter(vals[1], sprintf("%d %s", vals[0]+1, str));
}

private void read_letter(int x) {
    string tmp;

    if(__Options["content"])
        message("Nmail", sprintf("\n%%^INITTERM%%^信件 %d%s\n", (x+1),
                    (__Delete[x] ? " [已删除]:" : ":")), this_player());
    else message("Nmail", "\n%^INITTERM%^\n", this_player());
    if(__Options["content"]) tmp = header(__BoxInfo[x])+"\n";
    else tmp = "";
    tmp+=sprintf("\n%s\n",LETTERS_D->query_letter(__BoxInfo[x]["id"]));
    if(!__BoxInfo[x]["read"]) FOLDERS_D->mark_read(__Owner, __Folder, x);
    __BoxInfo[x]["read"] = 1;
    this_player()->eventPage(explode(tmp, "\n"), "mail", (: end_read :));
}

void end_read() {
    __FromMenu = 0;
    secondary_prompt();
    input_to("index_cmd");
}

nosave private void alias_members(string cmd, string args) {
    string *members, *old_members;
    string grp;

    if(args == "" || !args) {
        message("prompt", sprintf("%s哪个别名？\n",
                    (cmd == "e" ? "添加到" : "从")), this_player());
        input_to("get_alias", cmd);
        return;
    }
    if(sizeof(members = explode(args, " ")) == 1) {
        message("prompt", sprintf("%s哪些成员？\n",
                    (cmd == "e" ? "添加" : "删除")), this_player());
        input_to("get_members", ({ cmd, args }));
        return;
    }
    if(!sizeof(members -= ({ grp =  members[0] }))) {
        if(__CommandLine) destruct_box("别名成员无效。");
        else postal_error("别名成员无效。");
        return;
    }
    if(user_exists(grp = lower_case(grp)) ||
            LOCALPOST_D->query_mud_group(grp)) {
        if(__CommandLine) destruct_box("别名无效。");
        else postal_error("别名无效。");
        return;
    }
    if(!(old_members = OPTIONS_D->query_group(__Owner, grp))) {
        if(__CommandLine) destruct_box("没有该别名。");
        else postal_error(sprintf("没有名为 %s 的别名。", grp));
        return;
    }
    if(cmd == "e") members = distinct_array(members + old_members);
    else if(!sizeof(members = old_members - members)) members = 0;
    OPTIONS_D->set_group(__Owner, grp, members);
    if(cmd == "d") {
        if(!members)
            message("mail", "\n%^GREEN%^所有成员已删除。\n", this_player());
        else message("mail", "\n%^GREEN%^成员已从别名中删除。\n",
                this_player());
    }
    else message("mail", "\n%^GREEN%^成员已添加到别名中。\n",
            this_player());
    if(__CommandLine) this_object()->eventDestruct();
    else {
        secondary_prompt();
        input_to("alias_cmd");
    }
}

protected void get_alias(string str, string cmd) {
    if(str == "" || !str) {
        if(__CommandLine) destruct_box("别名名无效。");
        else postal_error("别名名无效。");
        return;
    }
    alias_members(cmd, str);
}

protected void get_members(string str, string *args) {
    if(str == "" || !str) {
        if(__CommandLine) destruct_box("别名成员无效。");
        else postal_error("别名成员无效。");
        return;
    }
    alias_members(args[0], sprintf("%s %s", args[1], str));
}

nosave private void alias_creation(string cmd, string args) {
    string *members;

    if(args == "" || !args) {
        message("prompt", sprintf("要%s的别名名称：\n",
                    (cmd == "m" ? "创建" : "删除")), this_player());
        input_to("get_alias_name", cmd);
        return;
    }
    if(cmd == "m" && sizeof(members=explode(args=lower_case(args)," ")) == 1) {
        message("prompt", "输入别名成员：\n", this_player());
        input_to("get_new_alias_members", ({ cmd, args }));
        return;
    }
    else if(cmd == "m") members = members - ({ args = members[0] });
    else members = 0;
    if(cmd == "m" && (user_exists(args) || LOCALPOST_D->query_mud_group(args))) {
        if(__CommandLine) destruct_box("别名名无效。");
        else postal_error("别名名无效。");
        return;
    }
    if(!(OPTIONS_D->query_group(__Owner, args))) {
        if(cmd == "r") {
            if(__CommandLine) destruct_box("没有该别名可删除。");
            else postal_error("没有该别名可删除。");
            return;
        }
    }
    else if(cmd == "m") {
        if(__CommandLine) destruct_box("该别名已存在。");
        else postal_error("该别名已存在。");
        return;
    }
    OPTIONS_D->set_group(__Owner, args, members);
    if(__CommandLine)
        destruct_box(sprintf("别名已%s。", (cmd == "m" ? "创建" : "删除")));
    else
        postal_success(sprintf("别名已%s。", (cmd == "m" ? "创建" : "删除")));
}

protected void get_alias_name(string str, string cmd) {
    if(str == "" || !str) {
        if(__CommandLine) destruct_box("别名名无效。");
        else postal_error("别名名无效。");
        return;
    }
    alias_creation(cmd, lower_case(str));
}

protected void get_new_alias_members(string str, string *args) {
    if(str == "" || !str) {
        if(__CommandLine) destruct_box("别名成员无效。");
        else postal_error("别名成员无效。");
        return;
    }
    alias_creation(args[0], sprintf("%s %s", args[1], lower_case(str)));
}

private void list_alias(string str) {
    string *who;

    if(str == "" || !str) {
        if(__CommandLine) destruct_box("别名名无效。");
        else postal_error("别名名无效。");
        return;
    }
    if(!(who = LOCALPOST_D->query_mud_group(str=lower_case(str)))) {
        who = OPTIONS_D->query_group(__Owner, str);
    }
    if(!who) {
        if(__CommandLine) destruct_box("该别名不存在。");
        else postal_error("该别名不存在。");
        return;
    }
    message("mail", "\n%^INITTERM%^"+center(sprintf("别名：%s", str),
                __Screen), this_player());
    message("mail", "\n\n"+implode(who, ",   "), this_player());
    if(__CommandLine) this_object()->eventDestruct();
    else {
        secondary_prompt();
        input_to("alias_cmd");
    }
}

private void save_options() {
    string *cles;
    int i;

    if(!__ChangedOptions) {
        postal_error("没有更改任何选项。");
        return;
    }
    i = sizeof(cles = keys(__ChangedOptions));
    while(i--)
        OPTIONS_D->set_option(__Owner, cles[i], __ChangedOptions[cles[i]]);
    __Options = OPTIONS_D->query_options(__Owner);
    postal_success("选项已保存。");
}

private void change_option(int x) {
    if(pointerp(__PostalOptions[x]["value"])) {
        message("mail", sprintf("%s\n\t0) %s\n\t1) %s\n",
            __PostalOptions[x]["desc"],
            __PostalOptions[x]["value"][0], __PostalOptions[x]["value"][1]),
            this_player());
    }
    else message("mail", __PostalOptions[x]["desc"], this_player());
    message("prompt", "请输入有效的值：\n", this_player());
    input_to("really_change_option", 0, x);
}

protected void really_change_option(string str, int x) {
    int y;

    if(!__ChangedOptions) __ChangedOptions = ([]);
    if(pointerp(__PostalOptions[x]["value"])) {
        if((y=to_int(str)) != 0 && y != 1) {
            postal_error("值无效。选项未更改。");
            return;
        }
        __ChangedOptions[__PostalOptions[x]["key"]] = y;
    }
    else __ChangedOptions[__PostalOptions[x]["key"]] = (str == "" ? 0 : str);
    postal_success("请记得保存后选项才会生效。");
}

private void reply(string str) {
    int x, i;

    if(str == "" || !str) x = __Current;
    else x = to_int(str)-1;
    if(x < 0 || x >= sizeof(__BoxInfo)) {
        postal_error("信件编号无效，无法回复。");
        return;
    }
    set_current(x);
    __TmpPost = ([ "date":time(), "from": this_player()->GetKeyName()]);
    if((__TmpPost["subject"] = __BoxInfo[x]["subject"])[0..2] != "Re:")
        __TmpPost["subject"] = sprintf("Re: %s", __TmpPost["subject"]);
    message("prompt", "包含原文吗（默认'n'）？\n", this_player());
    input_to("get_reply_confirm");
}

protected void get_reply_confirm(string str) {
    if(str == "" || !str) str = "n";
    else str = lower_case(str)[0..0];
    if(str == "y") __FwdRply = ({ "r", query_reply_text() });
    else if(str != "n") {
        message("prompt", "请输入 'y' 或 'n'：\n", this_player());
        input_to("get_reply_confirm");
        return;
    }
    else __FwdRply = 0;
    message("mail", sprintf("\n%s", center("回复给：a)全部, c)抄送列表和发件人, s)仅发件人, t)收件列表和发件人",__Screen)), this_player());
    message("prompt", "\n请选择（默认's'）：\n", this_player());
    input_to("get_reply_list");
}

protected void get_reply_list(string str) {
    int i;

    if(str == "" || !str) str = "s";
    else str = lower_case(str)[0..0];
    __TmpPost["to"] = ({ convert_name(__BoxInfo[__Current]["from"]) });
    switch(str) {
        case "a":
            __TmpPost["to"] += __BoxInfo[__Current]["to"];
            __TmpPost["cc"] = __BoxInfo[__Current]["cc"];
            break;
        case "c": __TmpPost["cc"] = __BoxInfo[i]["cc"]; break;
        case "s": __TmpPost["cc"] = ({}); break;
        case "t":
                  __TmpPost["to"] += __BoxInfo[__Current]["to"];
                  __TmpPost["cc"] = ({});
                  break;
        default:
                  message("prompt","选择无效。请重新选择：\n", this_player());
                  input_to("get_reply_list");
                  return;
    }
    if(!__Options["askcc"]) get_cc("");
    else {
        message("prompt", "抄送至：\n", this_player());
        input_to("get_cc");
    }
}

private string query_reply_text() {
    string tmp;

    tmp = LETTERS_D->query_letter(__BoxInfo[__Current]["id"]);
    return sprintf("\n>%s\n", replace_string(tmp, "\n", "\n>"));
}

nosave private void forward_letter(string str, int flag) {
    string *args;
    int i, x;

    if(str == "" || !str) {
        message("prompt", "收件人：\n", this_player());
        input_to("get_forward_list");
        return;
    }
    i = sizeof(args = explode(lower_case(str), " "));
    if(!flag) {
        while(i--) if(sscanf(args[i], "%d", x) && x) break;
        if(!x) x = __Current;
        else {
            x--;
            if( !i ) {
                if(sizeof(args) == 1) args = ({});
                else args = args[1..];
            }
            else if( i == sizeof(args)) {
                args = args[0..<2];
            }
            else if(sizeof(args) == 1)
                args = ({});
            else args = args[0..(i-1)] + args[(i+1)..];
        }
        if(x < 0 || x > sizeof(__BoxInfo)) {
            postal_error("信件编号超出范围。");
            return;
        }
        if(!sizeof(args)) {
            forward_letter(0, 1);
            return;
        }
    }
    set_current(x);
    __TmpPost["to"] = args;
    if((__TmpPost["subject"]=__BoxInfo[__Current]["subject"])[0..4] !=
            "(fwd)") __TmpPost["subject"] = sprintf("(fwd) %s",__TmpPost["subject"]);
    __TmpPost["from"] = this_player()->GetKeyName();
    __TmpPost["date"] = time();
    message("prompt", "对原信添加注释吗（默认'n'）？\n",
            this_player());
    input_to("confirm_comments");
}

protected void get_forward_list(string str) {
    if(str == "" || !str) {
        message("prompt","收件人无效。中止转发（默认'y'）？\n",
                this_player());
        input_to("confirm_forward_abort");
        return;
    }
    else forward_letter(str, 1);
}

protected void confirm_comments(string str) {
    if(str == "" || !str) str = "n";
    else str = lower_case(str)[0..0];
    if(str == "y") __FwdRply = ({ "f", query_forward_text() });
    else if(str == "n") {
        __FwdRply = 0;
        __TmpPost["message"] = query_forward_text();
    }
    else {
        message("prompt", "请输入 'y' 或 'n'：\n", this_player());
        input_to("confirm_comments");
        return;
    }
    if(!__Options["askcc"]) get_cc("");
    else {
        message("prompt", "抄送至：\n", this_player());
        input_to("get_cc");
    }
}

private string query_forward_text() {
    string tmp;

    tmp = LETTERS_D->query_letter(__BoxInfo[__Current]["id"]);
    tmp = ">"+replace_string(tmp, "\n", "\n>");
    return sprintf("原信由 %s 于 %s 发送：\n%s\n%s\n",
            capitalize(__BoxInfo[__Current]["from"]),
            postal_time(__BoxInfo[__Current]["date"]),
            center("---  ---    转发内容开始    ---  ---"), tmp);
}

protected void confirm_forward_abort(string str) {
    if(str == "" || !str) str = "y";
    else str = lower_case(str)[0..0];
    if(str == "y") {
        postal_error("转发已中止。");
        return;
    }
    else if(str != "n") {
        message("prompt", "请输入 'y' 或 'n'：\n", this_player());
        input_to("confirm_forward_abort");
        return;
    }
    message("prompt", "收件人：\n", this_player());
    input_to("get_forward_list");
}

private void send_letter(string *args) {
    string flag, tmp;
    int j, i, maxi, x;

    if(!args || !sizeof(args)) {
        message("prompt", "收件人：\n", this_player());
        input_to("get_to");
        return;
    }
    __FwdRply = 0;
    __TmpPost = ([ "from": this_player()->GetKeyName(),"date":time()]);
    for(i=0, maxi = sizeof(args); i<maxi; i++) {
        if(args[i] == "" || !args[i]) continue;
        if(!flag && i < maxi-1 && args[i][0] == '-' && strlen(args[i]) > 1) {
            if(member_array(args[i][1..1], ({"c","s","i"})) == -1)
                continue;
            else flag = args[i][1..1];
        }
        else if(!flag && args[i][0] == '\\' && strlen(args[i]) > 1)
            args[i] = args[i][1..strlen(args[1])-1];
        else if(flag) {
            if(args[i][0] != '\'') tmp = args[i];
            else if(args[i][x=strlen(args[i])-1] =='\'') tmp =args[i][1..x-1];
            else {
                tmp = args[j=i][1..x];
                while(++j < maxi && args[j][x=strlen(args[j])-1] != '\'')
                    if(x > 0) tmp += " "+args[j][0..x-1];
                if(args[j][x] == '\'' && x > 1) tmp += " "+args[j][0..x-1];
                i = j;
            }
            switch(flag) {
                case "c":
                    if(!__TmpPost["cc"]) __TmpPost["cc"] = ({});
                    __TmpPost["cc"] += ({ convert_name(tmp) });
                    break;
                case "s": __TmpPost["subject"] = tmp; break;
                case "i":
                          tmp=absolute_path(this_player()->get_path(),tmp);
                          if(sscanf(tmp,user_path(this_player())+"%s", flag) != 1 ||
                                  !(master()->valid_read(tmp,this_player()))) {
                              if(__CommandLine) {
                                  this_object()->eventDestruct();
                                  return;
                              }
                              __TmpPost = ([]);
                              postal_error("访问被拒绝。");
                              return;
                          }
                          if(!file_exists(tmp)) {
                              if(__CommandLine) {
                                  this_object()->eventDestruct();
                                  return;
                              }
                              __TmpPost = ([]);
                              postal_error(sprintf("文件 %s 不存在。",tmp));
                              return;
                          }
                          if(!(__TmpPost["message"] = read_file(tmp)))
                              __TmpPost["message"] = "空文件";
                          break;
            }
            flag = 0;
        }
        else {
            if(!grepp(args[i],"@")){
                if(!__TmpPost["to"]) __TmpPost["to"] = ({ trim(convert_name(args[i])) });
                else __TmpPost["to"] += ({ trim(convert_name(args[i])) });
            }
            else {
                if(!__TmpPost["to"]) __TmpPost["to"] = ({ trim(args[i]) });
                else __TmpPost["to"] += ({ trim(args[i]) });
            }
        }
    }
    if(!__TmpPost["to"]) {
        message("prompt", "收件人：\n", this_player());
        input_to("get_to");
        return;
    }
    if(!__TmpPost["subject"]) {
        message("prompt", "主题：\n ", this_player());
        input_to("get_subject");
        return;
    }
    else message("mail", sprintf("主题：%s", __TmpPost["subject"]),
            this_player());
    if(!__TmpPost["cc"] && __Options["askcc"]) {
        message("prompt", "抄送至：\n", this_player());
        input_to("get_cc");
        return;
    }
    else if(!__TmpPost["cc"]) __TmpPost["cc"] = ({});
    if(!__TmpPost["message"]) get_cc("");
    else {
        __TmpPost["message"] = sprintf("%s%s", __TmpPost["message"],
                query_signature());
        confirm_send();
    }
}

protected void get_to(string str) {
    if(str == "" || !str) {
        if(__CommandLine) {
            this_object()->eventDestruct();
            return;
        }
        postal_error("未指定收件人。邮件已中止。");
        return;
    }
    send_letter(explode(str, ","));
}

protected void get_subject(string str) {
    string tmp;

    if(str == "" || !str) {
        message("prompt", "未填写主题。继续吗（默认'n'）？\n",
                this_player());
        input_to("confirm_subject");
        return;
    }
    __TmpPost["subject"] = str;
    if(!__TmpPost["cc"] && __Options["askcc"]) {
        message("prompt", "抄送至：\n", this_player());
        input_to("get_cc");
        return;
    }
    else if(!__TmpPost["cc"]) __TmpPost["cc"] = ({});
    if(!__TmpPost["message"]) get_cc("");
    else {
        __TmpPost["message"] = sprintf("%s%s", __TmpPost["message"],
                query_signature());
        confirm_send();
    }
}

protected void confirm_subject(string str) {
    if(str == "" || !str) str = "n";
    else str = lower_case(str)[0..0];
    if(str == "n") {
        if(__CommandLine) {
            this_object()->eventDestruct();
            return;
        }
        __TmpPost = ([]);
        postal_error("邮件已中止。");
        return;
    }
    else if(str == "y") get_subject("[无主题]");
    else {
        message("prompt", "请输入 'y' 或 'n'：\n", this_player());
        input_to("confirm_subject");
        return;
    }
}

protected void get_cc(string str) {
    string tmp;

    if(!__TmpPost["cc"]) __TmpPost["cc"] = ({});
    if(str && str != "") __TmpPost["cc"] += explode(str, ",");
    if(__TmpPost["message"]) {
        __TmpPost["message"] = sprintf("%s%s", __TmpPost["message"],
                query_signature());
        confirm_send();
        return;
    }
    if(file_exists(tmp = tmpmail()))
        rm(tmp);
    if(!__FwdRply || __FwdRply[0] == "f") {
        message("mail",sprintf("\n%%^INITTERM%%^%s", header(__TmpPost)),
                this_player());
        this_player()->eventEdit(tmp, (: complete_send :));
        return;
    }
    write_file(tmp, __FwdRply[1]);
    message("mail", sprintf("\n%%^INITTERM%%^%s", header(__TmpPost)),
            this_player());
    this_player()->eventEdit(tmp, (: complete_send :));
}

void complete_send() {
    string str;

    if( !(str = read_file(tmpmail())))
        str = "无内容。";
    if(__FwdRply && __FwdRply[0] == "f")
        str = sprintf("%s\n%s\n%s", str, __FwdRply[1], query_signature());
    else str = sprintf("%s%s", str, query_signature());
    __TmpPost["message"] = str;
    __FwdRply = 0;
    confirm_send();
}

private string query_signature() {
    string tmp;

    if(!__Options["sig file"]) return "";
    if(strsrch(__Options["sig file"], " ") != -1)
        return sprintf("\n%s", __Options["sig file"]);
    tmp = absolute_path(homedir(this_player()),
            __Options["sig file"]);
    if(!(master()->valid_read(tmp, this_player())) || !file_exists(tmp)) {
        return sprintf("\n%s", __Options["sig file"]);
    }
    return read_file(tmp);
}

private void confirm_send() {
    message("mail", center("e)编辑, f)放弃, s)发送", __Screen), this_player());
    message("prompt", "\n命令（默认's'）：\n", this_player());
    input_to("handle_send_choice");
}

protected void handle_send_choice(string str) {
    string tmp = tmpmail();

    if(str == "" || !str) str = "s";
    else str = lower_case(str)[0..0];
    switch(str) {
        case "s":
            notify_send(LOCALPOST_D->send_post(copy(__TmpPost)));
            break;
        case "f":
            __TmpPost = ([]);
            postal_error("邮件已中止！");
            break;
        case "e":
            if(file_exists(tmp)) rm(tmp);
            write_file(tmp, __TmpPost["message"]);
            map_delete(__TmpPost, "message");
            this_player()->eventEdit(tmp, (: complete_send :));
            break;
        default:
            message("prompt", "无效命令。命令：\n", this_player());
            input_to("handle_send_choice");
            break;
    }
}

private void notify_send(string *failures) {
    string *arr;
    string tmp;

    if(!sizeof(failures))
        message("mail", "\n\t%^GREEN%^邮件发送成功！", this_player());
    else {
        message("mail", sprintf("\n发送失败，无法送达：%s",
                    implode(failures, ",  ")), this_player());
        if(creatorp(this_player())) {
            write_file(tmp=homedir()+"/tmp/dead.letter",
                    __TmpPost["message"]);
        }
        else write_file(tmp = sprintf("%s/%s.letter", homedir()+"/tmp",
                    this_player()->GetKeyName()), __TmpPost["message"]);
        message("mail", sprintf("信件副本已保存到 %s", tmp),
                this_player());
    }
    if(sizeof(arr=distinct_array(__TmpPost["to"]+__TmpPost["cc"])-failures))
        message("mail", sprintf("邮件已发送至：%s", implode(arr,",  ")),
                this_player());
    if(__CommandLine) {
        this_object()->eventDestruct();
        return;
    }
    secondary_prompt();
    input_to("index_cmd");
}

void incoming_post() {
    mixed tmp;
    string id;
    int *delete;

    if(__Folder != "new") return;
    if(file_name(previous_object()) != FOLDERS_D) return;
    id = (__Current < 0 ? 0 : __BoxInfo[__Current]["id"]);
    delete =map_array(tmp=FOLDERS_D->query_box_info(__Owner,"new"),
            "order_box", this_object());
    __BoxInfo = copy(tmp);
    set_current(id);
    __Delete = copy(delete);
    __IncomingFlag = 1;
}

int order_box(mapping borg) {
    int i;

    i = sizeof(__BoxInfo);
    while(i--) if(__BoxInfo[i]["id"] == borg["id"]) return __Delete[i];
    return 0;
}
