#include <lib.h>
#include <daemons.h>
#include NETWORK_H
#include SECRETS_H

inherit LIB_DAEMON;

void validate(){
    if(!master()->valid_apply(({ "SECURE"})) || !this_player()){
        error("no");
    }
    if(!archp(this_player()) || this_player()->GetForced()){
        error("i said no");
    }
}

mixed cmd(string str){
    mixed ret;
    int i, port;
    string cmd, args, name, addy;
    validate();
    if(!sizeof(str)) {
        write("尝试：help instconfig");
        return 1;
    }
    i = sscanf(str, "%s %s", cmd, args);
    if(!i) cmd = str;
    if(cmd == "create"){
        i = sscanf(args,"%s %s %d", name, addy, port);
        if(i != 3) i = sscanf(args,"%s %d", name, port);
        if(i < 2) {
            write("尝试：help instconfig");
            return 1;
        }
        if(undefinedp(addy)) addy = "127.0.0.1";
        ret = INSTANCES_D->InstCreate(name, addy, port);
        if(!ret){
            write("出现了某种问题。");
            return 1;
        }
        if(stringp(ret)) write(ret);
        else write("完成。");
        return 1;
    }

    if(cmd == "remove"){
        write("正在尝试移除："+args);
        if(member_array(args, INSTANCES_D->GetInstances()) == -1){
            write("未找到该实例。");
            return 1;
        }
        ret = INSTANCES_D->InstDelete(args);
        if(intp(ret)){
            write("成功移除 "+args+"。");
        }
        else {
            write(ret);
        }
        return 1;
    }
    if(cmd == "list"){
        mapping instdata = INSTANCES_D->GetInstData();
        mixed insts = sort_array(keys(instdata), 1);
        ret = "";
        foreach(mixed key in insts){
            if(!instdata[key]) continue;
            ret += key + " " + instdata[key]["port"] + " " +
                (instdata[key]["online"] ? "%^GREEN%^online" : "%^RED%^offline");
            ret += "%^RESET%^\n";
        }
        if(!sizeof(ret)){
            ret = "实例守护进程未发现任何已配置的实例。";
        }
        write(ret);   
        return 1;
    }
}

string GetHelp(){
    return ("语法：instconfig list\n"
            "        instconfig create <名称> <端口>\n"
            "        instconfig remove <名称>\n\n"
            "修改您的实例配置。要添加一个名为 Alpha、端口为 5555 的实例，请输入：\n"
            "instconfig create Alpha 5555\n\n"
            "要移除它：\n"
            "instconfig remove Alpha\n\n"
            "另见：instances, admintool, mudconfig");
}

