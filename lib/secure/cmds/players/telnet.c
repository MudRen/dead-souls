#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

mapping NamesMap = ([]);

mixed cmd(string args) {
    string ip_string, port_string, ip;
    int d1, d2, d3, d4, port;

    if(sscanf(args,"%s %s",ip_string, port_string) != 2){
        this_object()->help();
        return 1;
    }

    if(sscanf(ip_string,"%d.%d.%d.%d",d1,d2,d3,d4) != 4 &&
            !RESOLV_D->GetResolving()){
        write("本MUD没有使用域名解析。请使用数字IP地址，如 11.22.33.44");
        return 1;
    }

    if(!atoi(port_string)){
        write("端口必须是数字，如：6666");
        return 1;
    }

    if(d4){
        this_object()->eventStartConnection(this_player(), args);
        return 1;
    }

    write("正在尝试解析 \""+ip_string+"\"。如果失败，请尝试使用数字IP地址，如 1.2.3.4");
    NamesMap[ip_string] = ([ "dude": this_player(), "port" : port_string ]);
    RESOLV_D->eventResolve(ip_string, "resolve_callback");
    return 1;
}

void resolve_callback(string name, string number, int key){
    string cle, port;
    object ob;
    if(NamesMap[number]){
        cle = number;
    }
    else if(NamesMap[name]){
        cle = name;
    }
    else return;

    ob = NamesMap[cle]["dude"];
    port = NamesMap[cle]["port"];
    map_delete(NamesMap, cle);
    if(ob){
        ob->eventPrint(number+" 解析为：" + name);
        this_object()->eventStartConnection(ob, number + " " + port);
    }
}

int eventStartConnection(object who, string where){
    object client = new("/secure/obj/tc");
    if(!client || !who) return 0;

    if(!telnet_privp(who)){
        who->eventPrint("你没有使用本MUD telnet功能的权限。");
        return 1;
    }
    client->SetConnection(where);
    client->eventMove(who);
    client->do_connect(where, who);
    return 1;
}

string GetHelp(){
    return ("命令格式：telnet <IP地址> <端口>\n\n"
            "如果你在TELNET组中，此命令将连接到指定IP和端口的另一台计算机或MUD。");
}
