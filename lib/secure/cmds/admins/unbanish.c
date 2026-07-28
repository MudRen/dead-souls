//      /bin/adm/_unbanish.c
//      from the Dead Souls Mudlib
//      unbanishes a previously banished name
//      created by Shadowwolf@Dead Souls
//      rewritten for new security system by Descartes of Borg 930809

#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

int cmd(string str) {
    if(!archp(previous_object())) return 0;
    if(!str){
        write("语法: unbanish <字符串>");
        return 1;
    }
    write(capitalize(str = lower_case(str))+" 已解除封禁。\n");
    catch(call_other(BANISH_D, "unbanish_name", str));
    return 1;
}

string GetHelp(){
    return ("语法: unbanish <名称>\n\n"
            "从封禁名称列表中移除一个名称。");
}
