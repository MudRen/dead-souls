/*    /secure/cmds/player/bug.c
 *    from the Dead Souls Object Library
 *    the command interface to the NM IV bug tracking system
 *    created by Descartes of Borg 950925
 */

#include <lib.h>
#include <daemons.h>
#include <message_class.h>

inherit LIB_DAEMON;

void PreMenu(string str);
protected varargs void MainMenu(string str);
protected void Assign(string *args);
protected void EndAssign(string *args);
protected void Complete(string *args);
void EndComplete(int x);
protected void Delete(string *args);
protected void Report(string *args);
protected void EndReport(string type, string data, string file);
varargs protected void View(string *args, int print);
nosave string GetBugString(int id, mapping bugs);

protected void create() {
    daemon::create();
    SetNoClean(1);
}

mixed cmd(string str) {
    string *args;
    int i;

    if( !str || str == "" ) args = ({});
    else args = explode(str, " ");
    if( !(i = sizeof(args)) ) MainMenu();
    else {
        string opt;

        opt = args[0];
        if( i == 1 ) args = ({});
        else args = args[1..];
        switch(opt) {
            case "-a": Assign(args); break;
            case "-c": Complete(args); break;
            case "-d": Delete(args); break;
            case "-r": Report(args); break;
            case "-p": View(args, 1); break;
            case "-v": View(args); break;
            default: return "要报告bug，请使用 \"bug -r\"。";
        }
    }
    return 1;
}

void PreMenu(string str) {
    if( str == "q" ) {
        message("system", "退出bug追踪系统。", this_player());
        return;
    }
    MainMenu();
}

varargs protected void MainMenu(string str) {
    string tmp;
    int cols;

    if( str && str != "" ) {
        switch(str) {
            case "a": Assign(({})); return;
            case "c": Complete(({})); return;
            case "d": Delete(({})); return;
            case "r": Report(({})); return;
            case "p": View(({}), 1); return;
            case "v": View(({})); return;
            case "q":
                      message("system", "退出bug追踪系统。",
                              this_player());
                      return;
        }
    }
    cols = ((int *)this_player()->GetScreen())[0] || 80;
    tmp = center("Dead Souls Bug追踪系统", cols) + "\n\n";
    if( creatorp(this_player()) ) {
        tmp += "a) 将bug分配给创建者\n";
        tmp += "c) 完成bug的处理\n";
    }
    if( archp(this_player()) ) tmp += "d) 从系统中删除bug\n";
    tmp += "r) 向系统报告新bug\n";
    tmp += "v) 查看现有bug或bug列表\n";
    tmp += "\nq) 退出bug追踪系统\n";
    message("system", tmp, this_player());
    message("prompt", "请输入选择：", this_player());
    input_to( (: MainMenu :) );
}

protected void Assign(string *args) {
    int i;

    if( !creatorp(this_player()) ) {
        message("system", "只有创建者才能使用 -a 选项。",
                this_player());
        return;
    }
    if( !(i = sizeof(args)) ) {
        message("prompt", "请输入bug ID：", this_player());
        input_to(function(string str) { Assign(({ str })); });
        return;
    }
    else if( i == 1 ) {
        int x;

        if( (x = to_int(args[0])) > 0 ) { /* assume a bug id for now */
            if( !archp(this_player()) )
                Assign( ({ args[0], this_player()->GetCapName() }) );
            else {
                message("prompt", "请输入要分配给的创建者[" +
                        this_player()->GetCapName() + "]：",
                        this_player());
                input_to(function(string str, string id) {
                        if( !str || str == "" )
                        str = this_player()->GetCapName();
                        Assign( ({ str, id }) );
                        }, args[0]);
            }
            return;
        }
        else {
            message("prompt", "请输入要分配给" +
                    capitalize(args[0]) + "的bug ID：", this_player());
            input_to(function(string id, string str) {
                    Assign( ({ id, str }) );
                    }, args[0]);
            return;
        }
    }
    else if( i == 2 ) {
        message("prompt", "你想要添加评论吗？[n]：", this_player());
        input_to(function(string str, string *args) {
                if( !str || str == "" ) str = "n";
                else str = lower_case(str[0..0]);
                if( str == "y" ) {
                string file;

                message("system", "请输入关于bug的评论...",
                    this_player());
                file = DIR_TMP "/" + this_player()->GetKeyName();
                rm(file);
                this_player()->eventEdit(file, (: EndAssign, args :));
                return;
                }
                else Assign(args + ({ "" }));
                }, args);
        return;
    }
    else {
        string who, comments;
        int x;

        if( (x = to_int(args[0])) < 1 ) {
            who = args[0];
            if( (x = to_int(args[1])) < 1 ) {
                message("system", "无效的bug ID " + x + "。", this_player());
                message("prompt", "按回车键继续：", this_player());
                input_to( (: PreMenu :) );
                return;
            }
        }
        else who = args[1];
        comments = args[2];
        if( !archp(this_player()) && (convert_name(who) !=
                    this_player()->GetKeyName()) ) {
            message("system", "只有管理员才能将bug分配给其他人。",
                    this_player());
            message("prompt", "按回车键继续：", this_player());
            input_to( (: PreMenu :) );
            return;
        }
        if( !user_exists(convert_name(who)) ) {
            message("system", "没有该创建者：" + who, this_player());
            message("prompt", "按回车键继续：", this_player());
            input_to( (: PreMenu :) );
            return;
        }
        if( !(BUGS_D->eventAssign(x, who)) ) {
            message("system", "分配bug失败。", this_player());
            return;
        }
        if( comments != "" ) BUGS_D->AddComment(x, comments);
        message("system", "已将bug分配给" + who + "。", this_player());
        return;
    }
}

protected void EndAssign(string *args) {
    string file, contents;

    file = DIR_TMP "/" + this_player()->GetKeyName();
    contents = (read_file(file) || "");
    rm(file);
    Assign(args + ({ contents }));
}

protected void Complete(string *args) {
    string file;
    int x;

    if( !sizeof(args) ) {
        message("prompt", "请输入bug ID：", this_player());
        input_to(function(string str) { Complete( ({ str }) ); });
        return;
    }
    else if( !creatorp(this_player()) ) {
        message("system", "无效的命令。", this_player());
        message("prompt", "按回车键继续：", this_player());
        input_to( (: PreMenu :) );
        return;
    }
    else if( (x = to_int(args[0])) < 1 ) {
        message("system", "无效的bug ID。", this_player());
        message("prompt", "按回车键继续：", this_player());
        input_to( (: PreMenu :) );
        return;
    }
    message("system", "请输入你的评论：", this_player());
    file = DIR_TMP "/" + this_player()->GetKeyName();
    if( file_exists(file) ) rm(file);
    this_player()->eventEdit(file, (: EndComplete, x :));
}

void EndComplete(int x) {
    string file, stuff;

    if( previous_object() != this_player(1) ) return;
    file = DIR_TMP "/" + this_player()->GetKeyName();
    if( !(stuff = read_file(file)) ) {
        message("system", "编辑已取消。", this_player());
        rm(file);
        return;
    }
    rm(file);
    if( !(BUGS_D->eventComplete(x, stuff)) ) {
        message("system", "设置bug为已完成失败。", this_player());
        return;
    }
    message("system", "bug已标记为完成！", this_player());
}

protected void Delete(string *args) {
    if( !archp(this_player()) ) {
        message("system","只有管理员才能删除bug。", this_player());
        return;
    }
    if( !sizeof(args) ) {
        message("prompt", "要删除哪个bug？", this_player());
        input_to(function(string str) { Delete( ({ str }) ); });
        return;
    }
    else {
        int x;

        if( (x = to_int(args[0])) < 1 )
            message("system", "无效的bug ID。", this_player());
        else if( !(BUGS_D->eventDelete(x)) )
            message("system", "删除失败。", this_player());
        else message("system", "删除成功。", this_player());
        return;
    }
}

protected void Report(string *args) {
    if( archp(this_player()) && sizeof(args) ) {
        string data;
        string bug;
        int x;

        data = "Room: " + file_name(environment(this_player()));
        bug = implode(args, " ");
        if( x = BUGS_D->eventReport(this_player()->GetCapName(),
                    "approval", bug, data) ) {
            BUGS_D->eventAssign(x, query_privs(environment(this_player())));
            message("system", "bug已报告。", this_player());
            return;
        }
        else {
            message("system", "报告bug时出错。", this_player());
            return;
        }
    }
    else EndReport(0, "Room: " + file_name(environment(this_player())), 0);
}

protected void EndReport(string type, string data, string file) {
    string tmp;
    int x;

    if( !type ) {
        message("system", "请选择bug类型：\n",
                this_player());
        message("system", "\tidea（添加到游戏中的好主意）",
                this_player());
        message("system", "\ttypo（拼写错误、语法问题）",
                this_player());
        message("system", "\tunexplained behaviour（与预期不符的行为）",
                this_player());
        message("system", "\truntime（错误消息）\n",
                this_player());
        message("system", "\tother（其他）\n", this_player());
        message("prompt", "请输入类型：", this_player());
        input_to( (: EndReport :), data, 0);
        return;
    }
    if( !file ) {
        file = DIR_TMP "/" + this_player()->GetKeyName();
        rm(file);
        message("system", "请输入bug的描述。完成后，在空白行输入一个点（.）。",
                this_player());
        this_player()->eventEdit(file, (: EndReport, type, data, file :));
        return;
    }
    if( !(tmp = read_file(file)) ) {
        message("system", "bug报告已取消。", this_player());
        rm(file);
        return;
    }
    rm(file);
    if( type == "runtime" ) {
        mapping last_error;

        if( last_error = this_player()->GetLastError() )
            data += "\n" + master()->standard_trace(last_error) + "\n";
    }
    if( !(x = BUGS_D->eventReport(this_player()->GetCapName(),
                    type, tmp, data)) ) {
        message("system", "bug报告失败。", this_player());
        return;
    }
    message("system", "bug已报告，谢谢！你的追踪ID是 " +
            x + "。", this_player());
}

varargs protected void View(string *args, int print) {
    mapping bugs;
    function f;

    f = function() {
        message("prompt", "\n按回车键继续：", this_player());
        input_to( (: PreMenu :) );
    };
    if( !sizeof(args) ) {
        message("system", "查看：\n\t1) 所有bug\n"
            "\t2) 仅未分配的bug\n"
            "\t3) 仅已分配的bug\n"
            "\t4) 仅已完成的bug\n", this_player());
        if( creatorp(this_player()) )
            message("prompt", "请选择 [3]：", this_player());
        else message("prompt", "请选择 [1]：", this_player());
        input_to(function(string str, string it_sucks, int print) {
                if( !str || str == "" ) {
                if( creatorp(this_player()) ) str = "3";
                else str = "1";
                }
                if( str < "1" || str > "4" ) {
                message("system", "无效的选择", this_player());
                message("prompt", "按回车键继续：", this_player());
                input_to( (: PreMenu :) );
                return;
                }
                View( ({ str }), print );
                }, "", print);
        return;
    }
    else if( sizeof(args) == 1 && !creatorp(this_player()) ) {
        mapping bug;
        string tmp = "";
        int bug_id;

        bugs = BUGS_D->GetBugs();
        foreach( bug_id, bug in bugs ) {
            if( bug["who"] != this_player()->GetCapName() )
                continue;
            if( args[0] == "1" || (args[0] == "2" && !bug["assigned"]) ||
                    (args[0] == "3" && bug["assigned"] && !bug["date fixed"]) ||
                    (args[0] == "4" && bug["date fixed"]) )
                tmp += GetBugString(bug_id, bugs) + "\n*****\n\n";
        }
        if( tmp == "" ) {
            message("system", "没有符合条件的bug。",
                    this_player());
            message("prompt", "按回车键继续：", this_player());
            input_to( (: PreMenu :) );
            return;
        }
        this_player()->eventPage(explode(tmp, "\n"), MSG_SYSTEM, f);
        return;
    }
    else if( sizeof(args) == 1 ) {
        message("system", "查看：\n\t1) 所有bug\n"
            "\t2) 分配给我的bug\n"
            "\t3) 我报告的bug\n", this_player());
        message("prompt", "请选择 [2]：", this_player());
        input_to(function(string str, string one, int print) {
                if( !str || str == "" ) str = "2";
                else if( str < "1" || str > "3" ) {
                message("system", "无效的选择。", this_player());
                message("prompt", "按回车键继续：", this_player());
                input_to( (: PreMenu :) );
                return;
                }
                View( ({ one, str }), print );
                }, args[0], print);
        return;
    }
    else {
        mapping bug;
        string nom, tmp = "";
        int bug_id;

        nom = this_player()->GetKeyName();
        bugs = BUGS_D->GetBugs();
        if( !creatorp(this_player()) ) {
            View( ({ args[0] }), print );
            return;
        }
        else foreach(bug_id, bug in bugs) {
            string opt1, opt2;

            opt1 = args[0];
            opt2 = args[1];
            if( opt1 == "1" && opt2 == "1" )
                tmp += GetBugString(bug_id, bugs) + "\n*****\n\n";
            else {
                if( opt2 == "2" && (!bug["assigned"] ||
                            convert_name(bug["assigned"]) != nom) )
                    continue;
                else if(opt2 == "3" && convert_name(bug["who"]) != nom )
                    continue;
                if( opt1 == "2" && !bug["assigned"] )
                    tmp += GetBugString(bug_id, bugs) + "\n*****\n\n";
                else if( opt1 == "3" && bug["assigned"] && !bug["date fixed"] )
                    tmp += GetBugString(bug_id, bugs) + "\n*****\n\n";
                else if( opt1 == "4" && bug["date fixed"] )
                    tmp += GetBugString(bug_id, bugs) + "\n*****\n\n";
            }
        }
        if( tmp == "" ) {
            message("system", "没有匹配的bug。", this_player());
            message("prompt", "按回车键继续：", this_player());
            input_to( (: PreMenu :) );
            return;
        }
        if( print && creatorp(this_player()) ) {
            string file;

            rm(file = user_path(this_player()->GetKeyName()) + "bugs");
            write_file(file, strip_colours(tmp));
        }
        else this_player()->eventPage(explode(tmp, "\n"), MSG_SYSTEM, f);
        return;
    }
}

nosave string GetBugString(int id, mapping bugs) {
    string tmp;

    tmp = "%^YELLOW%^Bug ID:%^RESET%^ " + id + "\n";
    tmp += "%^YELLOW%^报告者：%^RESET%^" +
        bugs[id]["who"] + "\n";
    if( bugs[id]["assigned"] ) {
        tmp += "%^YELLOW%^状态：%^RESET%^";
        if( !bugs[id]["date fixed"] )
            tmp += "已分配给 " + bugs[id]["assigned"] + "\n";
        else tmp += "已完成 " + ctime(bugs[id]["date fixed"]) + "\n";
    }
    else tmp += "%^YELLOW%^状态：%^RESET%^未分配\n";
    tmp += "%^YELLOW%^类型：%^RESET%^" + bugs[id]["type"] + "\n";
    if( bugs[id]["date fixed"] )
        tmp += "%^YELLOW%^备注：%^RESET%^\n" + bugs[id]["resolution"] + "\n";
    if( creatorp(this_player()) )
        tmp += "\n%^YELLOW%^创建者信息：%^RESET%^\n" + bugs[id]["data"] + "\n";
    tmp += "\n%^YELLOW%^Bug信息：%^RESET%^\n" + bugs[id]["bug"] + "\n";
    return tmp;
}

string GetHelp(){
    string tmp;

    tmp = "命令格式：bug\n";
    if( creatorp(this_player()) ) {
        tmp += "        bug -a <BUG_ID 创建者>\n";
        tmp += "        bug -c <BUG_ID>\n";
    }
    if( archp(this_player()) ) tmp += "        bug -d <BUG_ID>\n";
    tmp += "        bug -r\n        bug -v [1-4] [1-3]\n\n";
    tmp += "Dead Souls Bug追踪系统的命令接口。"
        "你可以直接输入\"bug\"来获取进一步选项，"
        "或者如果你熟悉系统，可以直接使用命令行参数。"
        "这个系统允许玩家报告bug或建议，并定期查看报告的处理情况。"
        "它也为创建者提供了一种追踪已报告bug并向报告玩家反馈的方式。"
        "它为管理员提供了一种追踪和分配mudlib级别bug的方式。"
        "上述选项分别对应分配、完成、删除、报告和查看bug。\n"
        "参见：praise";
    return tmp;
}

