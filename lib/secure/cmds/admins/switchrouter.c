#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;

string file;

mixed cmd(string args) {
    string ip, name;
    int port, octet1, octet2, octet3, octet4;

    if(!archp(previous_object())) return "No.";

    if(!args || args == ""){
        object omud = find_object(INTERMUD_D);
        if(!omud){
            write("跨MUD守护进程未加载。尝试：help switchrouter");
            write("它可能已被禁用。尝试：help mudconfig");
            return 1;
        }
        name = omud->GetNameservers()[0][0];
        ip = omud->GetNameservers()[0][1];
        if(!name || !ip){
            write("您的跨MUD守护进程配置似乎有问题。");
            return 1;
        }
        write("您当前的直连路由器为 "+name+" "+ip);
        if(sizeof(omud->GetNameservers()) > 1){
            write("注意：您配置了多个路由器。"+
                    "您连接的路由器数组为："+identify(omud->GetNameservers()));
        }
        return 1;
    }

    if(find_object(INTERMUD_D))find_object(INTERMUD_D)->eventClearVars();
    if(find_object(INTERMUD_D))find_object(INTERMUD_D)->eventDestruct();


    if(args == "reload"){
        write("正在重新加载跨MUD守护进程。");
        if( load_object(INTERMUD_D) ) write("跨MUD守护进程已重新加载。");
        else write("重新加载跨MUD守护进程失败。");
        return 1;
    }

    if(sscanf(args,"%s %s %d", name, ip, port) != 3 || port > 65534 ||
            sscanf(ip,"%d.%d.%d.%d", octet1, octet2, octet3, octet4) != 4){
        write("无效的路由器引用。\n尝试：switchrouter <路由器名称> <数字IP> <端口>");
        write("例如：switchrouter yatmim 149.152.218.102 23");
        if( load_object(INTERMUD_D) ) write("跨MUD守护进程已重新加载。");
        else write("重新加载跨MUD守护进程失败。");
        return 1;
    }

    file = read_file(INTERMUD_D+".c");

    file = replace_matching_line(file, "//Nameservers", "");

    if(first(name,1) != "*") name = "*"+name;

    file = replace_matching_line(file, "Nameservers = ({",
         "    Nameservers = ({ ({ \""+name+"\", \""+ip+" "+port+"\" }) });", 1);

            unguarded( (: write_file(INTERMUD_D+".c",file,1) :) );

            if( load_object(INTERMUD_D) ) write("跨MUD守护进程已重新加载。");
            else write("重新加载跨MUD守护进程失败。");

            write("完成。");
            return 1;
            }

            string GetHelp(){
            return ("语法：switchrouter <名称> <IP> <端口>\n\n"
                "停止跨MUD守护进程，将默认跨MUD路由器"
                "更改为您指定的IP和端口，清除之前的"
                "路由器数据，并重新加载 INTERMUD_D。不带参数时，"
                "此命令将清除您的跨MUD缓存并重新加载"
                "守护进程。已知路由器：\n"
                "*dalet 97.107.133.86 8787（LPMuds.net \"官方\"路由器）\n"
                "*i4 204.209.44.3 8080（*dalet 的备用/替代路由器）\n"
                "Dead Souls 官方当前路由器的IP始终可在以下地址获取：\n"
                "http://dead-souls.net/router.html"
                "\n\n"
                "另见：mudlist, mudconfig, http://intermud.org");
            }

