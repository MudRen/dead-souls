#include <lib.h>
#include <cfg.h>
#include <save.h>
#include <daemons.h>
#include <commands.h>
#include NETWORK_H
#include <sockets.h>
string GetHelp();

inherit LIB_DAEMON;

string ret_string = "";
string* config, *config2, *keywords;
string* bools = ({ "enable","disable","on","off","1","0" });
string* yesbools = ({ "enable","on","1","yes" });
string* nobools = ({ "disable","off","0","no" });
string* restrict_tokens = ({ "restrict","unrestrict" });
string* nonmodals = ({ "liveupgrade", "prompt","status","email",
        "websourceip", "websourcename", "mudname", "mudport",
        "debugger", "access", "pinging", "pinginterval",
        "imc2serverpass", "imc2clientpass" });
string* antimodals = ({ "imc2", "ced" });
string* modals = antimodals + ({ "channelpipes", "fastcombat",
        "catchtell","matchcommand", "matchobject", "autowiz", "locked",
        "localtime", "justenglish", "justhumans", "encumbrance", "pk",
        "compat", "exitsbare", "nmexits", "grid", "minimap", "wizmap",
        "cgi", "dirlist", "creweb", "selectclass", "severable",
        "retain", "defaultparse", "disablereboot", "loglocal", "logremote",
        "questrequired", "autoadvance","guestallowed", "playerintertell" });
string* inet_services = ({ "oob", "hftp", "ftp", "http", "rcp", "inet" });

protected int NotImplemented(string which);
varargs nosave int TestFun(string which, string arg);
varargs nosave int ModIntermud(string which, string arg);
varargs nosave int ModRouter(string which, string arg);
nosave int ProcessModal(string which, string arg);
varargs nosave int ModStartRoom(string which, string arg);
nosave int ProcessOther(string which, string arg);
nosave int ProcessString(string which, string arg);
int ProcessInet(string which, string arg);
varargs nosave int ModDefaultDomain(string which, string arg);
varargs nosave int ModCfg(string which, string arg);

private void validate() {
    if(!this_player()) return 0;
    if( !(master()->valid_apply(({ "ASSIST" }))) )
        error("Illegal attempt to access mudconfig: "+get_stack()+" "+identify(previous_object(-1)));
}

mixed cmd(string str) {
    string which, arg;

    validate();

    if(this_player() && !securep(this_player())){
        write("此命令仅限完全管理员使用。要成为完全管理员，"+
                "您需要被添加到 SECURE 组。");
        return 1;
    }

    if(!this_player() && base_name(previous_object()) != IMC2_D &&
            base_name(previous_object()) != INTERMUD_D) return 1;

    if(base_name(previous_object()) == IMC2_D){
        if(str != "imc2 disable") return 1;
    }
    if(base_name(previous_object()) == INTERMUD_D){
        if(str != "intermud disable") return 1;
    }

    if(!str || sscanf(str, "%s %s", which, arg) != 2){
        write(GetHelp());
        return 1;
    }
    cp(CONFIG_H,"/secure/save/backup/config."+time());
    config = explode( read_file(CONFIG_H),"\n" );
    config2 = ({});
    keywords = ({});
    foreach(string element in config){
        string s1, s2;
        if(sscanf(element,"#define %s %s",s1,s2) == 2) keywords += ({ s1 });
    }

    if(member_array(which,modals) != -1){
        ProcessModal(which, arg);
        return 1;
    }

    if(member_array(which,inet_services) != -1){
        ProcessInet(which, arg);
        return 1;
    }

    else switch(which){
        case "test" : TestFun(which, arg);break;
        case "intermud" : ModIntermud(which, arg);break;
        case "router" : ModRouter(which, arg);break;
        case "startroom" : ModStartRoom(which, arg);break;
        case "defaultdomain" : ModDefaultDomain(which, arg);break;
        case "resets" : which = "TIME_TO_RESET";ProcessOther(which,arg);break;
        case "offset" : which = "GMT_OFFSET";ProcessOther(which,arg);break;
        case "extraoffset" : which = "EXTRA_TIME_OFFSET";ProcessOther(which,arg);break;
        case "newbielevel" : which = "MAX_NEWBIE_LEVEL";ProcessOther(which,arg);break;
        case "monitor" : which = "GLOBAL_MONITOR";ProcessOther(which,arg);break;
        case "maxip" : which = "SAME_IP_MAX";ProcessOther(which,arg);break;
        case "pinginterval" : which = "PING_INTERVAL";ProcessOther(which,arg);break;
        case "maxcommands" : which = "MAX_COMMANDS_PER_SECOND";ProcessOther(which,arg);break;
        case "maxidle" : which = "IDLE_TIMEOUT";ProcessOther(which,arg);break;
        case "instances" : which = "ENABLE_INSTANCES";ProcessOther(which,arg);break;
        case "hostip" : which = "HOST_IP";ProcessString(which,arg);break;
        case "email" : which = "ADMIN_EMAIL";ProcessString(which,arg);break;
        case "liveupgrade" : which = "LIVEUPGRADE_SERVER";ProcessString(which,arg);break;
        case "mudstatus" : which = "MUD_STATUS";ProcessString(which,arg);break;
        case "debugger" : which = "DEBUGGER";ProcessString(which,arg);break;
        case "websourceip" : which = "WEB_SOURCE_IP";ProcessString(which,arg);break;
        case "websourcename" : which = "WEB_SOURCE_NAME";ProcessString(which,arg);break;
        case "imc2clientpass" : which = "IMC2_CLIENT_PW";ProcessString(which,arg);break;
        case "imc2serverpass" : which = "IMC2_SERVER_PW";ProcessString(which,arg);break;
        case "mudname" : ModCfg("name", arg);break;
        case "mudport" : ModCfg("port", arg);break;
        default : NotImplemented(which);break;
    }
    return 1;
}

varargs protected int CompleteConfig(string file){
    string ret = implode(config2,"\n")+"\n";
    if(!file) file = CONFIG_H;
    validate();
    ret = replace_string(ret,"\n\n","\n");
    write_file(file,ret,1);
    RELOAD_D->ReloadBaseSystem();
    reload(LIB_CONNECT,0,1);
    reload(BANISH_D,0,1);
    reload(PLAYERS_D,0,1);
    write("命令完成。");
    return 1;
}

int ModPortOffset(string which, string arg){
    string out, service, svc, junk, offset, new_offset;
    string *new_array = ({});
    string netcfg = read_file(NETWORK_H);
    string *net_array = explode(netcfg,"\n");

    new_offset = arg;
    service = which;
    service = upper_case(service);
    foreach(string element in net_array){
        if(sscanf(element,"#define OFFSET_%s %s %d",svc, junk, offset) == 3){
            if(lower_case(svc) == lower_case(service)){
                out = "#define OFFSET_"+service+"               "+new_offset;
            }
            else out = element;
        }
        else out = element;
        new_array += ({ out });
    }
    out = implode(new_array,"\n");

    write_file(NETWORK_H,out,1);
    write(service+" 的端口偏移量已设置为 "+offset+"。");
    RELOAD_D->eventReload(this_object(), 1, 1);
    reload(MASTER_D,0,1);
    return 1;
}

int ModPort(string which, mixed arg){
    string out, service, svc, junk, new_offset, new_port;
    string *new_array = ({});
    string netcfg = read_file(NETWORK_H);
    string *net_array = explode(netcfg,"\n");
    int offset;

    if(stringp(arg)) new_port = arg;
    else new_port = itoa(arg);
    service = which;
    service = upper_case(service);
    foreach(string element in net_array){
        if(sscanf(element,"#define OFFSET_%s %s %d",svc, junk, offset) == 3){
            if(lower_case(svc) == lower_case(service)){
                new_offset = ""+(atoi(new_port) - query_host_port());
                out = "#define OFFSET_"+service+"               "+new_offset;
            }
            else out = element;
        }
        else out = element;
        new_array += ({ out });
    }
    out = implode(new_array,"\n");
    if(last(out,1) != "\n") out += "\n";
    write_file(NETWORK_H,out,1);
    write(service+" 的端口已设置为 "+atoi(new_port)+"。");
    write("要完成此配置，请等待2秒，然后执行以下命令：");
    write("mudconfig "+lower_case(service)+" disable");
    write("mudconfig "+lower_case(service)+" enable");
    RELOAD_D->eventReload(this_object(), 1, 1);
    reload(MASTER_D,0,1);
    return 1;
}

protected int NotImplemented(string which){
    validate();
    write("关键字 \""+which+"\" 尚未在 mudconfig 中实现。");
    return 1;
}

varargs nosave int TestFun(string which, string arg){
    validate();
    write("参数："+which+" 值："+arg);
    return 1;
}

varargs nosave int ModStartRoom(string which, string arg){
    if(!arg){
        write("请指定房间文件的绝对路径。");
        return 1;
    }
    if(first(arg,1) != "/"){
        write("您输入的是相对路径。请使用绝对路径重试。");
        return 1;
    }
    if(last(arg,2) == ".c") arg = truncate(arg,2);
    if(!file_exists(arg+".c")){
        write("该文件不存在。");
        return 1;
    }
    if(catch(load_object(arg))){
        write("/n/n该房间文件已损坏。请修复后重试。");
        return 1;
    }
    cp(ROOMS_H,"/secure/save/backup/rooms."+time());
    config = explode( read_file(ROOMS_H),"\n" );
    config2 = ({});
    foreach(string line in config){
        string s1,s2,s3;
        if(sscanf(line,"%s %s %s",s1,s2,s3) == 3){
            if(s1 == "#define" && s2 == "ROOM_START")
                line = "#define ROOM_START       \""+arg+"\"";
        }
        config2 += ({ line });
    }
    CompleteConfig(ROOMS_H);
    reload(LIB_CREATOR,1,1);
    write("\n注意：某些对象（如动词和工作间）仍然包含旧的 "+
            "START_ROOM 值。在它们被重新加载或 MUD 重启之前，"+
            "这不会改变。");
    return 1;
}

varargs nosave int ModDefaultDomain(string which, string arg){
    if(!arg){
        write("请指定域的绝对路径，例如：/domains/MystyShyre");
        return 1;
    }

    if(first(arg,1) != "/"){
        write("您输入的是相对路径。请使用绝对路径重试。"+
                "例如：mudconfig defaultdomain /domains/MystyShyre");
        return 1;
    }

    if(!directory_exists(arg)){
        write("该域不存在。输入：help domaincreate");
        return 1;
    }

    if(!directory_exists(arg+"/room")){
        write("该目录似乎缺少 /room 子目录。它不适合作为一个域。");
        return 1;
    }

    cp("/secure/include/dirs.h","/secure/save/backup/dirs."+time());
    config = explode( read_file("/secure/include/dirs.h"),"\n" );
    config2 = ({});
    foreach(string line in config){
        string s1,s2,s3;
        if(sscanf(line,"%s %s %s",s1,s2,s3) == 3){
            if(s1 == "#define" && s2 == "DIR_STANDARD_DOMAIN")
                line = "#define DIR_STANDARD_DOMAIN       \""+arg+"\"";
        }
        config2 += ({ line });
    }

    CompleteConfig("/secure/include/dirs.h");

    write("\n请重启 MUD 以使此更改生效。\n");
    return 1;
}

varargs nosave int ModRouter(string which, string arg){
    string preloads = read_file(CFG_PRELOAD);
    string *load_lines = explode(preloads,"\n");
    string *ret_arr = ({});
    string yesline = "/secure/daemon/i3router/server";
    string noline = "#/secure/daemon/i3router/server";
    validate();
    if(member_array(arg,bools) == -1){
        write("请重试，指明您要启用还是禁用跨MUD路由器。注意此设置将在重启后保留。");
        return 1;
    }

    if(member_array(arg,yesbools) != -1){
        if(member_array(yesline,load_lines) != -1) write("路由器持久化启动已处于启用状态。");
        else {
            write("正在启用路由器持久化启动。");
            foreach(string line in load_lines){
                if(line == noline) line = yesline;
                ret_arr += ({ line });
            }
            if(member_array(yesline,ret_arr) == -1){
                ret_arr += ({ yesline });
            }
            unguarded( (: cp(CFG_PRELOAD,"/secure/save/backup/preload."+time()) :) );
            ret_string = implode(ret_arr,"\n")+"\n";
            ret_string = replace_string(ret_string,"\n\n","\n");
            unguarded( (: write_file(CFG_PRELOAD,ret_string,1) :) );
        }
        if(find_object(ROUTER_D)) write("跨MUD路由器已在运行中。");
        else {
            write("正在启动跨MUD路由器。");
            load_object(ROUTER_D);
        }

        ret_string = "";
        write("跨MUD路由器已启用。");
        return 1;
    }

    if(member_array(arg,nobools) != -1){

        if(member_array(noline,load_lines) != -1) write("路由器持久化启动已处于禁用状态。");
        else {
            write("正在禁用路由器持久化启动。");
            foreach(string line in load_lines){

                if(line == yesline) line = noline;
                ret_arr += ({ line });
            }
            if(member_array(noline,ret_arr) == -1){
                ret_arr += ({ noline });
            }
            unguarded( (: cp(CFG_PRELOAD,"/secure/save/backup/preload."+time()) :) );
            ret_string = implode(ret_arr,"\n")+"\n";
            ret_string = replace_string(ret_string,"\n\n","\n");
            unguarded( (: write_file(CFG_PRELOAD,ret_string,1) :) );

        }
        if(!find_object(ROUTER_D)) write("跨MUD路由器未在运行。");
        else {
            write("正在停止跨MUD路由器。");
            find_object(ROUTER_D)->eventDestruct();
        }
        ret_string = "";
        write("跨MUD路由器已禁用。");
        return 1;
    }
}

varargs nosave int ModIntermud(string which, string arg){
    validate();
    write("参数："+which+" 值："+arg);
    if(arg == "restrict"){
        write("正在限制跨MUD通信...");
        flush_messages(this_player());
        foreach(string element in config){
            if(grepp(element, "RESTRICTED_INTERMUD")) element = "#define RESTRICTED_INTERMUD      1";
            config2 += ({ element });
        }
        CompleteConfig();
        reload(INTERMUD_D,0,1);
        reload(IMC2_D,0,1);
        reload("/daemon/services/tell",0,1);
        reload("/daemon/services",0,1);
        return 1;
    }

    if(arg == "reset"){
        object ob = find_object(INTERMUD_D);
        string savei3 = save_file(SAVE_INTERMUD);
        write("正在清除所有跨MUD数据（包括路由器密码！）。之前的数据文件已保存到 /secure/save/backup/ 。");
        if(!ob){
            if(file_exists(savei3)){
                rename(savei3, "/secure/save/backup/intermud."+time());
            }
        }
        else {
            if(file_exists(savei3)){
                rename(savei3, "/secure/save/backup/intermud."+time());
            }
            reload(INTERMUD_D,0,1);
        }
        config2 = config;
        CompleteConfig();
        return 1;
    }

    if(arg == "unrestrict"){
        write("正在解除跨MUD通信限制...");
        flush_messages(this_player());
        foreach(string element in config){
            if(grepp(element, "RESTRICTED_INTERMUD")) element = "#define RESTRICTED_INTERMUD      0";
            config2 += ({ element });
        }
        CompleteConfig();
        reload(INTERMUD_D,0,1);
        reload(IMC2_D,0,1);
        reload("/daemon/services/tell",0,1);
        return 1;
    }

    if(member_array(arg,bools) == -1){
        write("请重试，指明您要启用、禁用、限制、解除限制还是重置跨MUD通信。");
        return 1;
    }

    if(member_array(arg,yesbools) != -1){
        write("正在启用跨MUD通信...");
        flush_messages(this_player());
        foreach(string element in config){
            if(grepp(element, "DISABLE_INTERMUD")) element = "#define DISABLE_INTERMUD         0";
            config2 += ({ element });
        }
        CompleteConfig();
        reload(INTERMUD_D,0,1);
        return 1;
    }

    if(member_array(arg,nobools) != -1){
        write("正在禁用跨MUD通信...");
        if(this_player()) flush_messages(this_player());
        foreach(string element in config){
            if(grepp(element, "DISABLE_INTERMUD")) element = "#define DISABLE_INTERMUD         1";
            config2 += ({ element });
        }
        CompleteConfig();
        reload(INTERMUD_D,0,1);
        return 1;
    }
    return 1;
}

nosave int ProcessOther(string which, string arg){
    int junk;
    validate();

    if(sscanf(arg,"%d",junk) != 1){
        write("此参数需要一个整数作为参数。");
        return 1;
    }

    foreach(string element in config){
        if(grepp(element, which)){
            string s1, s2, s3;
            if(sscanf(element,"#define %s %s",s1,s2) != 2){
                write("严重问题。您应该立即恢复 "+
                        CONFIG_H+" 的备份。");
                return 1;
            }
            s3 = trim(s2);
            s2 = replace_string(s2,s3,arg);
            element = "#define "+s1+" "+s2;
        }
        config2 += ({ element });
    }
    CompleteConfig();
    if(which == "LOCAL_TIME" || which == "EXTRA_TIME_OFFSET" || which == "GMT_OFFSET"){
        reload("/secure/sefun/local_time",0,1);
        reload("/secure/sefun/time",0,1);
        reload("/secure/sefun/timestamp",0,1);
        reload("/secure/sefun/sefun",0,1);
        RELOAD_D->eventReload("/daemon/time",2);
        reload("/secure/cmds/creators/people",0,1);
        reload("/cmds/players/date",0,1);
        reload("/cmds/players/nextreboot",0,1);
        reload("/cmds/players/version",0,1);
        write("此配置更改需要几分钟才能完全生效。");
    }
    if(which == "GLOBAL_MONITOR") reload(SNOOP_D,0,1);
    if(which == "IDLE_TIMEOUT" || which == "MAX_NEWBIE_LEVEL" ||
            which == "FAST_COMBAT" || which == "GRID" || which == "WIZMAP" ||
            which == "MINIMAP"){
        reload(LIB_CREATOR,1,1);
        write("此配置将在每个用户下次登录时生效。");
        return 1;
    }
    if(which == "PING_INTERVAL") reload (PING_D,1,1);
    return 1;
}

nosave int ProcessString(string which, string arg){
    object ob;
    validate();

    if(!strsrch(which, "IMC2_")){
        SECRETS_D->SetSecret(which, arg);
        reload(SECRETS_D, 0, 1);
        reload(IMC2_D, 0, 1);
        config2 = config;
        CompleteConfig();
        return 1;
    }

    foreach(string element in config){
        if(grepp(element, which)){
            string s1, s2, s3;
            if(sscanf(element,"#define %s %s",s1,s2) != 2){
                write("严重问题。您应该立即恢复 "+
                        CONFIG_H+" 的备份。");
                return 1;
            }
            s3 = trim(s2);
            s2 = replace_string(s2,s3,"\""+arg+"\"");
            element = "#define "+s1+" "+s2;
        }
        config2 += ({ element });
    }
    if(!strsrch(which, "WEB_SOURCE")
            && ob = find_object(CMD_LIVEUPGRADE)){
        ob->eventDestruct();
    }
    CompleteConfig();
    return 1;
}

nosave int ProcessModal(string which, string arg){
    int junk;
    validate();
    if(!arg){
        arg = "no";
        write("未提供参数：假定您要禁用此功能。");
    }
    if(member_array(arg,yesbools) != -1) junk = 1;
    if(member_array(arg,nobools) != -1) junk = 0;
    if(member_array(which,antimodals) != -1) junk = ( junk ^ 1 );

    if(junk) junk = 1;
    else junk = 0;
    arg = itoa(junk);

    if(sscanf(arg,"%d",junk) != 1){
        write("此参数是模态或准模态参数。它需要一个整数作为参数，或者至少需要 \"yes\" 或 \"no\"。");
        return 1;
    }

    if(member_array(upper_case(which),keywords) != -1){
        which = upper_case(which);
    }
    else switch(lower_case(which)){
        case "autowiz" : which = "AUTO_WIZ";break;
        case "locked" : which = "MUD_IS_LOCKED";break;
        case "localtime" : which = "LOCAL_TIME";break;
        case "justenglish" : which = "ENGLISH_ONLY";break;
        case "justhumans" : which = "HUMANS_ONLY";break;
        case "encumbrance" : which = "ENABLE_ENCUMBRANCE";break;
        case "pk" : which = "PLAYER_KILL";break;
        case "compat"  : which = "COMPAT_MODE";break;
        case "retain" : which = "RETAIN_ON_QUIT";break;
        case "defaultparse" : which = "DEFAULT_PARSING";break;
        case "disablereboot" : which = "DISABLE_REBOOTS";break;
        case "exitsbare" : which = "BARE_EXITS";break;
        case "nmexits" : which = "NM_STYLE_EXITS";break;
        case "matchcommand" : which = "COMMAND_MATCHING";break;
        case "matchobject" : which = "OBJECT_MATCHING";break;
        case "catchtell" : which = "NPC_CATCH_TELL_DEBUG";break;
        case "loglocal" : which = "LOG_LOCAL_CHANS";break;
        case "logremote" : which = "LOG_REMOTE_CHANS";break;
        case "imc2" : which = "DISABLE_IMC2";break;
        case "fastcombat" : which = "FAST_COMBAT";break;
        case "channelpipes" : which = "CHANNEL_PIPES";break;
        case "cgi" : which = "ENABLE_CGI";break;
        case "dirlist" : which = "WWW_DIR_LIST";break;
        case "creweb" : which = "ENABLE_CREWEB";break;
        case "selectclass" : which = "CLASS_SELECTION";break;
        case "severable" : which = "SEVERABLE_LIMBS";break;
        case "questrequired" : which = "REQUIRE_QUESTING";break;
        case "autoadvance" : which = "AUTO_ADVANCE";break;
        case "ced" : which = "CED_DISABLED";break;
        case "minimap" : which = "MINIMAP";break;
        case "wizmap" : which = "WIZMAP";break;
        case "grid" : which = "GRID";break;
        case "guestallowed" : which = "GUEST_ALLOWED";break;
        case "playerintertell" : which = "PLAYER_INTERTELL_ALLOWED";break;
        case "guest" : which = "GUEST_ALLOWED";break;
        default : break;
    }
    foreach(string element in config){
        if(grepp(element, which)){
            string s1, s2, s3;
            if(sscanf(element,"#define %s %s",s1,s2) != 2){
                write("严重问题。您应该立即恢复 "+
                        CONFIG_H+" 的备份。");
                return 1;
            }
            s3 = trim(s2);
            s2 = replace_string(s2,s3,arg);
            element = "#define "+s1+" "+s2;
        }
        config2 += ({ element });
    }
    CompleteConfig();
    if(which == "DEFAULT_PARSING" || which == "ENABLE_ENCUMBRANCE" ||
            which == "BARE_EXITS" || which == "COMMAND_MATCHING" ||
            which == "AUTO_ADVANCE"){
        reload(LIB_CREATOR,1,1);
        write("此配置将在每个用户下次登录时生效。");
        return 1;
    }
    if(which == "NPC_CATCH_TELL_DEBUG"){
        if(file_exists("/domains/default/room/catchtell"))
            reload("/domains/default/room/catchtell");
        return 1;
    }
    if(which == "CED_DISABLED"){
        reload(CMD_CED,1,1);
        reload(LIB_CREATOR,1,1);
        write("此配置将在每个用户下次登录时生效。");
    }
    if(which == "NM_STYLE_EXITS"){
        reload(LIB_ROOM,1,1);
        reload(LIB_CREATOR,1,1);
        write("此配置将在尚未加载的房间中对每个用户下次登录时生效。"+
                "要确保所有房间都应用新配置，"+
                "请重启 MUD，或输入：\"reload every room\"，然后退出并重新登录。");
    }
    if(which == "RETAIN_ON_QUIT" || which == "OBJECT_MATCHING")
        write("要使此配置生效，请重启 MUD。");
    if(which == "LOG_LOCAL_CHANS" || which == "LOG_REMOTE_CHANS"){
        reload(CHAT_D,1,1);
    }
    if(which == "DISABLE_IMC2"){
        object ob;
        IMC2_D->UnSetAutoDisabled(1);
        ob = find_object(IMC2_D);
        if(!junk && ob){
            reload(ob, 0, 1);
            reload(find_object(CHAT_D), 0, 1);
        }
        else IMC2_D->remove();
    }
    if(which == "FAST_COMBAT"){
        reload(LIB_CREATOR,1,1);
        write("此配置将在每个用户下次登录时生效。");
    }

    if(which == "ENABLE_CGI" || which == "WWW_DIR_LIST" || which == "ENABLE_CREWEB"){
        reload(WEB_SESSIONS_D,1,1);
        reload(SOCKET_HTTP,1,1);
        foreach(string element in get_dir(DIR_WWW_GATEWAYS+"/")){
            if(last(element,2) == ".c") reload(DIR_WWW_GATEWAYS+"/"+element,1,1);
        }
    }
    return 1;
}

int ProcessService(string which, string what){
    int port_offset, type, port;
    string sclass;
    if(sscanf(what,"port %d",port)){
        what = "port";
    }
    switch(which){
        case "hftp": port_offset=OFFSET_HFTP;sclass="/secure/lib/net/h_ftpd";type=1;break;
        case "ftp": port_offset=OFFSET_FTP;sclass="/secure/lib/net/ftp";type=1;break;
        case "http": port_offset=OFFSET_HTTP;sclass="/secure/lib/net/http";type=3;break;
        case "rcp": port_offset=OFFSET_RCP;sclass="/secure/lib/net/remote";type=1;break;
        case "oob": port_offset=OFFSET_OOB;sclass="/secure/lib/net/oob";type=0;break;
    }
    switch(what){
        case "add": INET_D->AddService(which,port_offset, sclass, type);break;
        case "remove": INET_D->RemoveService(which);break;
        case "start": INET_D->eventStartServer(which);break;
        case "restart": INET_D->eventRestartServer(which,1);break;
        case "stop": INET_D->eventStopServer(which);break;
        case "port": ModPort(which, port);break;
    }
    if(which == "oob"){
        if( what == "start" || what == "restart")
            reload(OOB_D);
        if( what == "stop" )
            OOB_D->eventDestruct();
    }
    write("完成。");
    return 1;
}

int ProcessInet(string which, string arg){
    int sub;
    string preloads = read_file(CFG_PRELOAD);
    string *load_lines = explode(preloads,"\n");
    string *ret_arr = ({});
    string yesline = "/secure/daemon/inet";
    string noline = "#/secure/daemon/inet";
    validate();
    if(!arg) arg = "status";
    if(which != "inet"){
        sub = 1;
        if(!find_object(INET_D)){
            write("inet 服务未运行。请输入：mudconfig inet start");
            write("或：mudconfig inet enable");
            write("然后重试您的命令。");
            return 1;
        }
    }
    else {
        if(member_array(arg,yesbools) != -1){
            if(member_array(yesline,load_lines) != -1) {
                write("inet 持久化启动已处于启用状态。");
                return 1;
            }
            else {
                write("正在启用 inet 持久化启动。");
                foreach(string line in load_lines){
                    if(line == noline) line = yesline;
                    ret_arr += ({ line });
                }
                if(member_array(yesline,ret_arr) == -1){
                    ret_arr += ({ yesline });
                }
                unguarded( (: cp(CFG_PRELOAD,"/secure/save/backup/preload."+time()) :) );
                ret_string = implode(ret_arr,"\n")+"\n";
                ret_string = replace_string(ret_string,"\n\n","\n");
                unguarded( (: write_file(CFG_PRELOAD,ret_string,1) :) );
                write("inet 服务已启用。");
                arg = "start";
            }
        }

        if(member_array(arg,nobools) != -1){
            if(member_array(noline,load_lines) != -1){
                write("inet 持久化启动已处于禁用状态。");
                return 1;
            }
            else {
                write("正在禁用 inet 持久化启动。");
                foreach(string line in load_lines){

                    if(line == yesline) line = noline;
                    ret_arr += ({ line });
                }
                if(member_array(noline,ret_arr) == -1){
                    ret_arr += ({ noline });
                }
                unguarded( (: cp(CFG_PRELOAD,"/secure/save/backup/preload."+time()) :) );
                ret_string = implode(ret_arr,"\n")+"\n";
                ret_string = replace_string(ret_string,"\n\n","\n");
                unguarded( (: write_file(CFG_PRELOAD,ret_string,1) :) );
                write("inet 服务已禁用。");
                arg = "stop";
            }
        }

        if(arg == "start"){
            if(find_object(INET_D)) write("inet 服务已在运行中。");
            else {
                write("正在启动 inet 服务。");
                load_object(INET_D);
            }
        }
        else if(arg == "stop"){
            if(!find_object(INET_D)) write("inet 服务已经停止。");
            else {
                write("正在停止 inet 服务。");
                find_object(INET_D)->eventDestruct();
            }
        }
        else if(arg == "restart"){
            if(find_object(INET_D)) {
                write("inet 服务正在运行。正在停止...");
                find_object(INET_D)->eventDestruct();
            }
            write("正在启动 inet 服务。");
            load_object(INET_D);
        }
        else if(arg == "status"){
            if(member_array(yesline,load_lines) != -1){
                write("inet 持久化启动已启用。");
            }
            else {
                write("inet 持久化启动已禁用。");
            }

            if(!find_object(INET_D)){
                write("inet 服务未运行");
            }
            else{
                string *servkeys, *servkeys2;
                string subret = "以下服务可用：";
                string subret2 = "以下服务正在运行：";
                write("inet 服务正在运行");
                if(sizeof(servkeys = keys(INET_D->GetServices()))){
                    subret += implode(servkeys,", ")+".\n";
                }
                else subret = "";
                if(sizeof(servkeys2 = keys(INET_D->GetServers()))){
                    subret2 += implode(servkeys2,", ")+".\n";
                }
                else subret2 = "";
                write(subret+subret2);
                return 1;
            }
            ret_string = "";
            write("完成。");
            return 1;
        }
        else write("不支持的 inet 子命令。");
        return 1;
    }
    if(arg == "enable"){
        if(INET_D->GetService(which)){
            write(which+" 服务已处于启用状态。您想要启动或重启它吗？");
            return 1;
        }
        ProcessService(which,"add");
        return 1;
    }
    if(arg == "disable"){
        if(!(INET_D->GetService(which))){
            write(which+" 服务已处于禁用状态。");
            return 1;
        }
        ProcessService(which,"remove");
        return 1;
    }

    if(arg == "start"){
        if(INET_D->GetServer(which)){
            write(which+" 服务已经启动。您想要重启它吗？");
            return 1;
        }
        if(!(INET_D->GetService(which))){
            write(which+" 服务已被禁用或不可用。");
            return 1;
        }
        ProcessService(which,"start");
        return 1;
    }
    if(arg == "stop"){
        if(!(INET_D->GetService(which))){
            write(which+" 服务已被禁用，因此未在运行。");
            return 1;
        }
        if(!(INET_D->GetServer(which))){
            write(which+" 服务已经停止。");
            return 1;
        }
        ProcessService(which,"stop");
        return 1;
    }

    if(arg == "restart"){
        ProcessService(which,"restart");
        return 1;
    }
    if(arg == "status"){
        write(which+" 服务"+(INET_D->GetService(which) ? "已启用。" : "已禁用。"));
        if(INET_D->GetService(which))
            write(which+" 服务"+(INET_D->GetServer(which) ? "正在运行。" : "已停止。"));
        return 1;
    }
    if(!strsrch(arg,"port ")){
        ProcessService(which,arg);
        return 1;
    }
    write("不支持的 mudconfig inet 服务子命令。");
    return 1;
}

varargs nosave int ModCfg(string which, string arg){
    int port, oldport, newport, ret, justbooted;
    string *line_array;
    string mconfig, nameline, portline, newline, newfile;
    string line_string, junk, name;
    object i3, imc2;

    justbooted = uptime() - 62;
    if(justbooted < -1){
        write("请等待 "+abs(justbooted)+" 秒后重试。");
        return 1;
    }

    if(!find_object(INSTANCES_D) || !ENABLE_INSTANCES ||
            INSTANCES_D->GetMyInstanceName() == "global"){
        port = 0;
        mconfig = "/secure/cfg/mudos.cfg";
    }
    else {
        port = query_host_port();
        mconfig = "/secure/cfg/mudos."+port+".cfg";
    }
    line_string = read_file(mconfig);
    if(!sizeof(line_string)) write("无法读取文件。");
    line_array = explode(line_string, "\n");
    if(!sizeof(line_array)) write("数组长度为零。");

    if(!sizeof(line_array) || !sizeof(line_string)) {
        return 1;
    }

    foreach(string line in line_array){
        if(!strsrch(line,"name :")){
            nameline = line;
            if(which == "name") break;
        }
        if(!strsrch(line,"external_port_")){
            portline = line;
            if(which == "port"){
                newport = atoi(arg);
                break;
            }
        }
    }

    if(which == "name"){
        if(!nameline || sscanf(nameline,"%s : %s",junk, name) < 2) {
            write("操作失败。您需要立即用原始副本覆盖 "+
                    mconfig+"。");
            return 1;
        }

        newline = junk + " : " + arg;
        newfile = replace_string(line_string, nameline, newline);
        write_file(mconfig,newfile,1);
        cp(mconfig,"/secure/cfg/mudos.autobak."+query_host_port());
        if(query_windows()){
            if(port){
                cp(mconfig,"/secure/cfg/mudos."+port+".win32");
            }
            else {
                cp(mconfig,"/secure/cfg/mudos.win32");
            }
        }
        imc2 = find_object(IMC2_D);
        i3 = find_object(INTERMUD_D);
        if(imc2) imc2->eventDestruct();
        if(i3) i3->eventDestruct();
        if(imc2) destruct(imc2);
        if(i3) destruct(i3);
        ret = MASTER_D->SetMudName(arg);
        write("\n");
        write("\nMUD 的名称已更改为："+mud_name());
        if(!DISABLE_IMC2){
            write("正在重新加载 IMC2...");
            catch(reload(IMC2_D, 0, 1));
        }
        if(!DISABLE_INTERMUD){
            write("正在重新加载 Intermud-3...");
            catch(reload(INTERMUD_D, 0, 1));
        }
        catch(reload(PING_D, 0, 1));
    }

    if(which == "port"){
        if(!portline || sscanf(portline,"%s : telnet %d",junk, oldport) < 2){
            write("操作失败。您需要立即用原始副本覆盖 "+
                    "/secure/cfg/mudos.cfg。");
            return 1;
        }

        newline = junk + " : telnet " + newport;
        newfile = replace_string(line_string, portline, newline);
        write_file("/secure/cfg/mudos.cfg",newfile,1);
        cp(mconfig,"/secure/cfg/mudos.autobak."+query_host_port());
        if(query_windows()){
            if(port){
                cp(mconfig,"/secure/cfg/mudos."+newport+".win32");
            }
            else {
                cp(mconfig,"/secure/cfg/mudos.win32");
            }
        }
        write("\nMUD 端口已更改。请重启 MUD 以激活新端口。");
        write("注意：如果您选择的端口是 1024 或以下，您的操作系统"+
                "可能要求 MUD 以特权用户身份运行。");
    }
    return 1;
}

string GetHelp(){
    return ("语法：mudconfig 参数 值 \n\n"
            "修改各种系统设置。\n"
            "示例：\n"
            "\nmudconfig autowiz [ yes | no ]"
            "\nmudconfig locked [ yes | no ]"
            "\nmudconfig justenglish [ yes | no ]"
            "\nmudconfig justhumans [ yes | no ]"
            "\nmudconfig encumbrance [ yes | no ]"
            "\nmudconfig severable [ yes | no ]（战斗中是否可以"
        "截断肢体。需要热重启。）"
            "\nmudconfig pk [ yes | no ]"
            "\nmudconfig minimap [ yes | no ]（玩家是否获得小地图）"
            "\nmudconfig wizmap [ yes | no ]（创造者是否获得区域地图）"
            "\nmudconfig grid [ yes | no ]（启用或禁用房间网格"
        "系统）"
            "\nmudconfig compat [ yes | no ]"
            "\nmudconfig retain [ yes | no ]"
            "\nmudconfig defaultparse [ yes | no ]"
            "\nmudconfig disablereboot [ yes | no ]"
            "\nmudconfig matchcommand [ yes | no ]"
            "\nmudconfig matchobject [ yes | no ]"
            "\nmudconfig exitsbare [ yes | no ]"
            "\nmudconfig nmexits [ yes | no ]（切换默认"
            "出口的显示方式）"
            "\nmudconfig fastcombat [ yes | no ]（战斗中覆盖"
            "心跳速率）"
            "\nmudconfig selectclass [ yes | no ]（新玩家"
            "登录时是否选择职业）"
            "\nmudconfig instances [ yes | no ]（是否使用"
            "MUD 实例）"
            "\nmudconfig localtime [ yes | no ]"
            "\nmudconfig offset <距GMT的偏移秒数>"
            "\nmudconfig extraoffset <距GMT的偏移小时数>"
            "\nmudconfig maxcommands <每秒最大命令数>"
            "\nmudconfig maxidle <自动退出前的空闲秒数>"
            "\nmudconfig questrequired [ yes | no ]"
            "\nmudconfig autoadvance [ yes | no ]"
            "\nmudconfig guestallowed [ yes | no ]"
            "\nmudconfig playerintertell [ yes | no ]"
            "\nmudconfig ced [ yes | no ]（切换全屏编辑器）"
            "\nmudconfig maxip <每IP最大连接数>"
            "\nmudconfig pinginterval <I3 ping间隔秒数>"
            "\nmudconfig monitor <监控级别，0到2>"
            "\nmudconfig newbielevel <最大新手等级>"
            "\nmudconfig resets <重置间隔>"
            "\nmudconfig router [ enable | disable ]"
            "\nmudconfig startroom <起始房间文件名>"
            "\nmudconfig defaultdomain </完整/路径>"
            "\nmudconfig email <管理员邮箱地址>"
            "\nmudconfig liveupgrade <默认热更新MUD名称>"
            "\nmudconfig hostip <计算机IP地址"
            "（如 111.222.333.444）>"
            "\nmudconfig websourceip <远程Web服务器IP地址"
            "（如 111.222.333.444）>"
            "\nmudconfig websourcename <远程Web服务器IP名称"
            "（如 a.b.com）>"
            "\nmudconfig channelpipes [ enable | disable ]（是否允许"
            "管道消息。不推荐。）"
            "\nmudconfig intermud [ enable | disable | restrict | "
            "unrestrict | reset ]"
            "\nmudconfig imc2 [ enable | disable ]"
            "\nmudconfig imc2clientpass <IMC2客户端密码>"
            "\nmudconfig imc2serverpass <IMC2服务器密码>"
            "\nmudconfig inet [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig ftp [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig hftp [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig rcp [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig oob [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig http [ enable | disable | start | stop | restart "
            "| status ]"
            "\nmudconfig cgi [ enable | disable ]（MUD Web服务器"
            "是否使用CGI）"
            "\nmudconfig dirlist [ enable | disable ]（允许Web服务器"
            "显示目录内容）"
            "\nmudconfig creweb [ enable | disable ]（允许基于Web的"
            "编辑[需要cgi和dirlist]）"
            "\nmudconfig loglocal [ enable | disable ]（是否记录"
            "本地频道）"
            "\nmudconfig logremote [ enable | disable ]（是否记录"
            "远程频道）"
            "\nmudconfig mudname <名称>"
            "\nmudconfig mudport <端口>"
            "\n\n另见：admintool, config");
}

