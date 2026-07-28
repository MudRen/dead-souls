#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    if(!member_group(previous_object(), "SECURE")) {
        if(!member_group(previous_object(), "LAW")) return 0;
    }
    if(!str) {
        notify_fail("正确语法: unallow [名称]\n");
        return 0;
    }
    if(member_array(str = lower_case(str), 
                BANISH_D->query_allowed()) == -1) {
        notify_fail(capitalize(str)+" 未被设置为允许进入。\n");
        return 0;
    }
    BANISH_D->unallow_name(str);
    log_file("watch/players", previous_object()->GetKeyName()+
            " UNLETIN "+str+": "+ctime(time())+"\n");
    return 1;
}

string GetHelp(){
    return ("语法: unallow <名称>\n\n"
            "从允许被封禁站点玩家创建新角色的名称列表中移除一个名称。\n"
            "另见:\nletin, wholetin, banish, whobanished, unbanish, "
            "register, unregister, whoregistered");
}
