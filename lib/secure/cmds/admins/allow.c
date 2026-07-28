//	/bin/adm/_allow.c
//	from the Dead Souls mudlib
//	lets in selected players from sites on register
//	created by Shadowwolf@Dead Souls?

#include <lib.h>
#include <privs.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    string who, email;
    mixed res;

    if(!archp(previous_object())) return 0;
    if(!member_group(previous_object(), PRIV_SECURE)) {
        if(!member_group(previous_object(), "LAW")) {
            notify_fail("只有法律组才能允许新玩家进入游戏。\n");
            return 0;
        }
    }
    if(!str) return 0;
    if(sscanf(lower_case(str), "%s %s", who, email) != 2) {
        notify_fail("语法: allow <玩家名> <邮箱>\n");
        return 0;
    }
    if(user_exists(who)) {
        notify_fail("该名称的角色已存在。\n");
        return 0;
    }
    write(capitalize(who)+" 现在被允许创建角色。\n");
    if(res = catch(call_other(BANISH_D, "allow_name", who)))
        write("允许 "+who+" 进入时出错: "+res+"\n");
    log_file("watch/players", capitalize(who)+": "+email+" ("+ctime(time())+")\n");
    return 1;
}

string GetHelp(){
    return "语法: allow <玩家名> <邮箱>\n\n"
        "法律组成员可以使用此命令允许来自注册站点的人员创建"
        "新角色。<玩家名>是角色名称，<邮箱>是玩家的真实"
        "电子邮箱地址。另见: whobanished, whoregistered, whowatched";
}

