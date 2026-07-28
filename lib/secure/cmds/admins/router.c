#include <lib.h>
#include <save.h>
#include <daemons.h>

inherit LIB_DAEMON;
mapping mudlist;
string banned, unbanned;
string blacklisted, unblacklisted;
string *allmuds, *banned_arr, *unbanned_arr;
string *blacklisted_arr, *unblacklisted_arr;

varargs string match_mud_name(string mud, string *list){
    list = allmuds;
    if(member_array(mud, list) != -1) return mud;
    foreach(string element in list){
        if(lower_case(element) == lower_case(mud)) {
            return element;
        }
    }
    foreach(string element in list){
        if(!strsrch(lower_case(element), lower_case(mud))){
            return element;
        }
        if(mudlist[element]["ip"]+" "+mudlist[element]["player_port"] == mud)
            return mudlist[element]["name"];
    }
    return "";
}

mixed cmd(string args) {
    string arg1, arg2, tmp;
    int scannedp;
    object router = find_object(ROUTER_D);

    if(!archp(previous_object())) return 0;

    if(!router && (args != "on" && args != "online")){
        write("路由器未加载。请先尝试：mudconfig router enable");
        return 1;
    }

    mudlist = router->query_mudinfo();
    allmuds = keys(mudlist);

    if(!args || args == ""){
        args = "show";
    }

    if(args == "show"){
        write("路由器配置：");
        router->get_info();
        return 1;
    }

    if(!router){
        write("路由器未加载。");
        return 1;
    }

    scannedp = sscanf(args,"%s %s", arg1, arg2);

    if(args == "mudlist" || arg1 == "mudlist"){
        mapping info;
        string *list;
        mapping borg;
        string mud, tempy;
        int all = 0;
        int ipsort = 0;
        int fdsort = 0;
        if(sizeof(arg2)) tempy = match_mud_name(arg2);
        if(sizeof(tempy)) arg2 = tempy;
        if(arg2 && !strsrch(arg2,"-i")){
            ipsort = 1;
            arg2 = trim(arg2[2..]);
        }
        if(arg2 && !strsrch(arg2,"-f")){
            fdsort = 1;
            arg2 = trim(arg2[2..]);
        }

        if( arg2 && arg2 != "" && strlen(arg2) > 3 ) {
            mapping tmp_map;
            string opt, tmpstr;

            tmp_map = mudlist;
            if( arg2[0] != '-' ) arg2 = "-n " + arg2;
            opt = arg2[1..1];
            arg2 = arg2[3..];
            borg = ([]);

            foreach(mud, info in tmp_map) {
                int x, y, z;

                switch(opt) {
                    case "a":
                        all = 1;
                        break;
                    case "m":
                        x = 5;
                        break;
                    case "d":
                        x = 7;
                        break;
                    case "n":
                        x = 0;
                        break;
                }
                tmpstr = (x ? info[x] : mud);
                z = strlen(arg2 = replace_string(lower_case(arg2), " ", ""));
                y = strlen(tmpstr = replace_string(lower_case(tmpstr), " ", ""));
                if( lower_case(arg2) == lower_case(tmpstr) ) {
                    borg = ([ mud : info ]);
                    break;
                }
                else if( y > z && tmpstr[0..z-1] == arg2 && info[0] == -1 ) 
                    borg[mud] = info;
            }
        }
        else {
            borg = ([ ]);
            foreach( mud, info in mudlist ){
                if( all == 1 || (info["restart_delay"] && info["restart_delay"] == -1) ) 
                    borg[mud] = info;
            }
        }
        if( !sizeof(borg) ) {
            message("system", "没有MUD匹配您的查询。", this_player());
            return 1;
        }
        else if( sizeof(borg) == 1 ) {
            string msg, svc;
            int val, comma = 0;

            mud = keys(borg)[0];
            msg = "\nDetailed information on %^GREEN%^" + mud + "%^RESET%^:\n";
            msg += sprintf("MUD Type: %:-6s Server: %:-20s Library: %s\n",
                    borg[mud]["mud_type"], borg[mud]["driver"], borg[mud]["base_mudlib"]);
            msg += "Status: " + borg[mud]["open_status"] + "\nAdmin email: " +
                borg[mud]["admin_email"] + "\n";
            msg += "Services: ";
            foreach(svc, val in borg[mud]["services"]) {
                if( val == 1 ) {
                    if( comma ) msg += ", " + svc;
                    else {
                        msg += svc;
                        comma = 1;
                    }
                }
            }
            msg += "\nHost: " + borg[mud]["ip"] + "\n";
            msg += "Telnet port: " + borg[mud]["player_port"] + "\n";
            if( borg[mud]["services"]["amcp"] )
                msg += "AMCP version: " + borg[mud]["services"]["amcp"] + "\n";
            if( borg[mud]["services"]["http"] ) 
                msg += "HTTP port (World Wide Web): " + borg[mud]["services"]["http"]+"\n";
            if( borg[mud]["services"]["ftp"] ) 
                msg += "FTP port (File Transfer): " + borg[mud]["services"]["ftp"] + "\n";
            if( borg[mud]["services"]["rcp"] )
                msg += "RCP port (Remote Creator): " + borg[mud]["services"]["rcp"] + "\n";
            message("info", msg, this_player());
            return 1;
        }

        list = ({});

        if(fdsort){
            mapping fds = ROUTER_D->query_connected_fds();
            string *ret = ({});
            int i, quant = sizeof(socket_status());
            for(i = 0; i < quant; i++){
                if(last_string_element(socket_status(i)[3],".") == ROUTER_D->GetRouterPort() ){
                    string mudnamen;
                    if(fds[i]) mudnamen = fds[i];
                    else mudnamen = "UNKNOWN";
                    ret += ({ i+" "+mudnamen+" "+explode(socket_address(i)," ")[0] });
                }
            }
            ret = sort_array(ret,1);
            this_player()->eventPage(ret);
            return 1;
        }

        foreach(mud, info in borg){
            if(ipsort)
                list += ({ sprintf("%:-15s %:-6s %:-15s %:-18s",
                            info["ip"], itoa(info["player_port"]), replace_string(mud,"%^","%%^^"), info["base_mudlib"]) });

            else
                list += ({ sprintf("%:-15s %:-6s %:-15s %:-18s %s %d",
                            replace_string(mud,"%^","%%^^"), info["mud_type"], info["driver"], info["base_mudlib"], info["ip"], info["player_port"]) });
        }
        list = sort_array(list, 1);
        list = ({ replace_string(mud_name(),"%^","%%^^") + " 共识别出 " + consolidate(sizeof(borg), "一个MUD")+
                " 匹配您的查询：", "" }) + list;
        this_player()->eventPage(list);
        return 1;
    }

    if(args == "reload" || args == "restart" || args == "reset"){
        object rsocket = find_object(RSOCKET_D);
        if(router){
            if(args == "reset"){
                router->clear();
                router->irn_clear();
            }
            router->SetList();
            router->eventDestruct();
            router = find_object(ROUTER_D);
            if(router) write("路由器卸载失败。");
            else write("路由器已从内存中卸载。");
            flush_messages();
        }
        if(args == "restart" || args == "reset"){
            if(rsocket) rsocket->eventDestruct();
            if(rsocket) destruct(rsocket);
            if(rsocket) write("%^RED%^BOLD%^路由器套接字未销毁。%^RESET%^");
            rsocket = load_object(RSOCKET_D);
            if(!rsocket) write("无法重新加载路由器套接字守护进程。");
        }
        write("正在加载路由器守护进程...");
        flush_messages();
        router = load_object(ROUTER_D);
        if(!router) write("路由器加载失败。");
        else write("路由器已加载。");
        return 1;
    }

    if(args == "on" || args == "online"){
        if(router){
            write("路由器守护进程已在线。");
            return 1;
        }
        else {
            write("正在加载路由器守护进程...");
            flush_messages();
            router = load_object(ROUTER_D);
            if(!router) write("路由器加载失败。");
            else write("路由器已加载。");
            return 1;
        }
    }

    if(args == "off" || args == "offline"){
        if(!router){
            write("路由器守护进程已离线。");
            return 1;
        }
        else {
            write("正在卸载路由器守护进程...");
            flush_messages();
            router->eventDestruct();
            router = find_object(ROUTER_D);
            if(router) write("路由器卸载失败。");
            else write("路由器已从内存中卸载。");
            return 1;
        }
    }

    if(!router){
        write("跨MUD路由器未加载。");
        return 1;
    }

    if(!arg2) arg1 = args;

    if(arg1 == "ban" || arg1 == "banned"){
        if(sizeof(router->GetBannedMuds())) banned_arr = router->GetBannedMuds();
        else banned_arr = ({});
        if(!sizeof(banned_arr)) banned = "没有被封禁的MUD。";
        else banned = implode(banned_arr,", ");
        if(!arg2){
            write("被封禁的MUD："+banned);
            return 1;
        }
        tmp = match_mud_name(arg2, allmuds);
        if(!sizeof(tmp)){
            write("没有这个MUD，但我仍将把该名称添加到列表中。");
        }
        else arg2 = tmp;

        router->AddBannedMud(arg2);
        write(arg2+" 已被添加到封禁列表。");
        return 1;
    }

    if(arg1 == "unban" || arg1 == "unbanned"){
        if(sizeof(router->GetBannedMuds())) banned_arr = router->GetBannedMuds();
        else banned_arr = ({});
        if(!sizeof(banned_arr)) unbanned = "没有被封禁的MUD。";
        else {
            banned = implode(banned_arr,", ");
            unbanned_arr = filter(keys(mudlist), (: member_array($1, banned_arr) == -1 :) ) || ({});
            unbanned = implode(unbanned_arr,", ");
        }
        if(!arg2){
            write("未被封禁的MUD："+unbanned);
            return 1;
        }

        router->RemoveBannedMud(arg2);
        write(arg2+" 已从封禁列表中移除。");
        return 1;
    }

    if(arg1 == "blacklist" || arg1 == "blacklisted"){
        if(sizeof(router->GetBlacklistedMuds())) blacklisted_arr = router->GetBlacklistedMuds();
        else blacklisted_arr = ({});
        if(!sizeof(blacklisted_arr)) blacklisted = "没有被列入黑名单的MUD。";
        else blacklisted = implode(blacklisted_arr,", ");
        if(!arg2){
            write("被列入黑名单的MUD："+blacklisted);
            return 1;
        }
        tmp = match_mud_name(arg2, allmuds);
        if(!sizeof(tmp)){
            write("没有这个MUD，但我仍将把该名称添加到列表中。");
        }
        else arg2 = tmp;

        router->AddBlacklistedMud(arg2);
        write(arg2+" 已被添加到黑名单。");
        return 1;
    }

    if(arg1 == "unblacklist" || arg1 == "unblacklisted"){
        if(sizeof(router->GetBlacklistedMuds())) blacklisted_arr = router->GetBlacklistedMuds();
        else blacklisted_arr = ({});
        if(!sizeof(blacklisted_arr)) unblacklisted = "没有被列入黑名单的MUD。";
        else {
            blacklisted = implode(blacklisted_arr,", ");
            unblacklisted_arr = filter(keys(mudlist), (: member_array($1, blacklisted_arr) == -1 :) ) || ({});
            unblacklisted = implode(unblacklisted_arr,", ");
        }
        if(!arg2){
            write("未被列入黑名单的MUD："+unblacklisted);
            return 1;
        }

        router->RemoveBlacklistedMud(arg2);
        write(arg2+" 已从黑名单中移除。");
        return 1;
    }

    if(arg1 == "id" || arg1 == "identify"){
        if(!arg2){
            write("要识别哪个MUD？");
            return 1;
        }
        tmp = match_mud_name(arg2, allmuds);
        if(!sizeof(tmp)){
            write("未找到该MUD。");
            return 1;
        }
        else arg2 = tmp;

        write("正式名称为："+arg2);
        return 1;
    }


    if(arg1 == "config"){
        string s1, s2, s3;
        if(arg2 && sizeof(arg2)){
            arg2 = reverse_string(arg2);
            sscanf(arg2,"%s %s %s", s3, s2, s1);
        }
        if(s1){
            s1 = reverse_string(s1);
            if(!strsrch(s1,"*")) true();
            else s1 = "*"+s1;
        }
        if(!s3){
            write("语法：router config 名称 IP 端口");
            return 1;
        }
        if(s2) s2 = reverse_string(s2);
        s3 = reverse_string(s3);
        router->SetRouterName(s1);
        router->SetRouterIP(s2);
        router->SetRouterPort(s3);
        router->SetRouterList();
        write("配置完成。要激活，请输入：router reset");
        return 1;
    }

    if(arg1 == "deletemud"){
        if(!arg2 || !sizeof(arg2)){
            write("语法：router deletemud MUD名称");
            return 1;
        }
        arg2 = match_mud_name(arg2, allmuds);
        router->remove_mud(arg2, 1);
        write("MUD已删除。");
        return 1;
    }

    if(arg1 == "name"){
        if(!arg2 || !sizeof(arg2)){
            write("语法：router name 名称");
            return 1;
        }
        router->SetRouterName(arg2);
        write("路由器名称已设置。");
        return 1;
    }


    if(arg1 == "ip"){
        if(!arg2 || !sizeof(arg2)){
            write("语法：router ip 地址");
            return 1;
        }
        router->SetRouterIP(arg2);
        write("路由器IP已设置。");
        return 1;
    }


    if(arg1 == "port"){
        if(!arg2 || !sizeof(arg2)){
            write("语法：router port 端口号");
            return 1;
        }
        router->SetRouterPort(arg2);
        write("路由器端口已设置。");
        return 1;
    }

    if(arg1 == "irn"){
        if(!arg2){
            write("请指定一个irn子命令：enable, disable, "
                    "check, force。");
            return 1;
        }
        if(arg2 == "check"){
            ROUTER_D->irn_checkstat();
            write("已发出irn状态检查。");
            return 1;
        }
        if(arg2 == "enable"){
            if(ROUTER_D->query_irn_enabled()){
                write("irn已处于启用状态。");
                return 1;
            }
            ROUTER_D->toggle_irn(1);
            ROUTER_D->irn_checkstat();
            write("irn已启用。");
            return 1;
        }
        if(arg2 == "disable"){
            if(!(ROUTER_D->query_irn_enabled())){
                write("irn已处于禁用状态。");
                return 1;
            }
            ROUTER_D->toggle_irn(0);
            ROUTER_D->irn_clear();
            write("irn已禁用。");
            return 1;
        }
        if(arg2 == "force"){
            ROUTER_D->toggle_irn(1);
            ROUTER_D->irn_setup(1);
            write("irn已强制重新加载。");
            return 1;
        }
    }

    write("路由器命令已完成。");
    return 1;
}

string GetHelp(){
    return ("语法：router [子命令 [参数]]\n\n"
            "不带参数时，显示路由器状态。\n"
            "示例：\n"
            "router reload : 重启路由器但不断开连接\n"
            "router restart : 重启路由器并断开所有连接\n"
            "router reset : 类似restart，但还会清除所有已保存的MUD信息\n"
            "router irn [enable|disable|check|force] : 管理IRN子系统\n"
            "router ban : 列出被封禁的MUD\n"
            "router ban <MUD名称> : 封禁名为<MUD名称>的MUD\n"
            "router unban <MUD名称> : 解除封禁\n"
            "router blacklist : 列出黑名单中的名称和IP\n"
            "router blacklist [名称 | IP地址] : 更严格的封禁\n"
            "router unblacklist [名称 | IP地址] : 解除黑名单\n"
            "router config <名称> <IP> <端口> : 一行配置路由器\n"
            "router port <端口号> : 设置路由器端口\n"
            "router ip <IP地址> : 设置IP地址，如 11.22.33.44\n"
            "router name <路由器名称> : 设置路由器名称\n"
            "router mudlist : 显示已知MUD的信息\n"
            "router mudlist -i : 按IP排序显示MUD\n"
            "router mudlist -f : 按文件描述符排序显示已连接的MUD\n"
            "\n"
            "要使路由器上线或离线，请使用 "
            "mudconfig 命令。");
}
