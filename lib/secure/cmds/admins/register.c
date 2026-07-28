//	/bin/adm/_register.c
//	from the Dead Souls mudlib
//	for restricting access for certain sites
//	created by Shadowwolf@Dead Souls?
// Edit stuff added by Manny@Dead Souls 940819

#include <lib.h>
#include <daemons.h>
#include <dirs.h>

inherit LIB_DAEMON;

void end_edit(string site);
void abort();

int cmd(string str) {
    if(!archp(previous_object())) return 0;
    if(!str) {
        notify_fail("语法: register <站点IP>\n\n");
        return 0;
    }
    write("%^RED%^请输入所有相关信息，包括名称、"
            "违规原因和邮箱地址。");
    rm(DIR_TMP+"/"+this_player()->GetKeyName()+".tmp");
    this_player()->eventEdit( DIR_TMP "/" + this_player()->GetKeyName(),
            (: end_edit($(str)) :));
    return 1;
}

void end_edit(string site) {
    string *lines;
    string tmpfile, res, str;
    int x, num;

    tmpfile = read_file(DIR_TMP+"/"+this_player()->GetKeyName());
    rm(DIR_TMP+"/"+this_player()->GetKeyName());
    if(tmpfile){
        tmpfile = replace_string(tmpfile, "\n", " ");
    }
    else {
        write("未写入任何内容。注册操作已取消。");
        return;
    }
    num = sizeof(lines = explode(wrap(tmpfile, 60), "\n"));
    str = " - "+site+" placed on Registration\n";
    str += "   by "+previous_object()->GetName()+": "+
        ctime(time())+"\n";
    for(x=0; x<num; x++) 
        str +=  "      * "+lines[x]+"\n";

    if(res = catch(call_other(BANISH_D, "register_site", site))) 
        write("注册站点时出错: "+res+"\n");

    log_file("watch/register", "\n" + str);
    write("%^RED%^%^BOLD%^"+site+" 现已加入注册列表！");
}

void abort() {
    rm(DIR_TMP+"/"+this_player()->GetKeyName()+".tmp");
    write("%^RED%^站点未注册！");
}

string GetHelp(){
    return "语法: register <站点>\n\n"
        "使指定站点需要在法律组注册角色后才能玩MUD。"
        "必须给出原因，且原因必须合理。通常只有法律组"
        "应该使用此命令。如果你不是法律组成员，最好给法律组发邮件。"
        "此命令仅适用于数字地址，例如:\n"
        "    register 134.181.*                可以\n"
        "    register 134.181.1.12             可以\n"
        "    register orlith.bates.edu         不行\n"
        "另见: unbanish, whobanished, whoregistered, whowatched";
}
