#include <lib.h>
#include <daemons.h>
#include <message_class.h>
inherit LIB_ROOM;

int ftp, hftp, http, rcp, i3, oob;

string LongDesc(){
    string ret = "这个房间就像它北边的网络室，"+
        "但它接收来自此MUD可以运行的各种网络服务器的消息。"+
        "如果此MUD不作为网络服务器，这个房间应该很安静。"+
        "否则这可能是你MUD上最吵闹的房间。\n";
    ret += "FTP服务器监控："+(ftp?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "HFTP服务器监控："+(hftp?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "HTTP服务器监控："+(http?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "RCP服务器监控："+(rcp?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "I3服务器监控："+(i3?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "OOB服务器监控："+(i3?"%^GREEN%^在线%^RESET%^":"%^RED%^离线%^RESET%^")+"\n";
    ret += "\n要启用服务器监控，你可以输入：\n"
        "i3 on\n"
        "ftp on\n"
        "hftp on\n"
        "http on\n"
        "rcp on\n"
        "oob on\n";
    return ret;
}

protected void create() {
    object ob;
    i3 = 1;
    oob = 1;
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("服务器监控室");
    SetLong( LongDesc() );
    SetExits(([
                "north" : "/secure/room/network",
                ]));
}

int CanReceive(object ob) {
    if( !archp(ob)  ){
        message("info","服务器监控室仅供管理员使用，抱歉。",ob);
        return 0;
    }
    return 1;
}

varargs int eventPrint(string msg, mixed arg2, mixed arg3){
    if(arg2 == MSG_FTP && !ftp) return 0;
    if(arg2 == MSG_HFTP && !hftp) return 0;
    if(arg2 == MSG_HTTP && !http) return 0;
    if(arg2 == MSG_RCP && !rcp) return 0;
    if(arg2 == MSG_I3 && !i3) return 0;
    if(arg2 == MSG_OOB && !oob) return 0;
    return ::eventPrint(msg, arg2, arg3);
}

void init(){
    ::init();
    add_action("ListenFTP","ftp");
    add_action("ListenHFTP","hftp");
    add_action("ListenHTTP","http");
    add_action("ListenRCP","rcp");
    add_action("ListenI3","i3");
    add_action("ListenOOB","oob");
}

int ListenI3(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(i3){
            write("这个房间已经在接收i3数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了i3数据监控。");
        say("你启用了i3数据监控。");
        i3 = 1;
        return 1;
    }
    if(!i3){
        write("这个房间已经在屏蔽i3数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了i3数据监控。");
    say("你禁用了i3数据监控。");
    i3 = 0;
    return 1;
}

int ListenFTP(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(ftp){
            write("这个房间已经在接收ftp数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了ftp数据监控。");
        say("你启用了ftp数据监控。");
        ftp = 1;
        return 1;
    }
    if(!ftp){
        write("这个房间已经在屏蔽ftp数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了ftp数据监控。");
    say("你禁用了ftp数据监控。");
    ftp = 0;
    return 1;
}

int ListenHFTP(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(hftp){
            write("这个房间已经在接收hftp数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了hftp数据监控。");
        say("你启用了hftp数据监控。");
        hftp = 1;
        return 1;
    }
    if(!hftp){
        write("这个房间已经在屏蔽hftp数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了hftp数据监控。");
    say("你禁用了hftp数据监控。");
    hftp = 0;
    return 1;
}

int ListenHTTP(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(http){
            write("这个房间已经在接收http数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了http数据监控。");
        say("你启用了http数据监控。");
        http = 1;
        return 1;
    }
    if(!http){
        write("这个房间已经在屏蔽http数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了http数据监控。");
    say("你禁用了http数据监控。");
    http = 0;
    return 1;
}

int ListenRCP(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(rcp){
            write("这个房间已经在接收rcp数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了rcp数据监控。");
        say("你启用了rcp数据监控。");
        rcp = 1;
        return 1;
    }
    if(!rcp){
        write("这个房间已经在屏蔽rcp数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了rcp数据监控。");
    say("你禁用了rcp数据监控。");
    rcp = 0;
    return 1;
}

int ListenOOB(string str){
    if(!str || (str != "on" && str != "off")){
        write("请指定你要开启还是关闭。");
        return 1;
    }
    if(str == "on"){
        if(oob){
            write("这个房间已经在接收oob数据了。");
            return 1;
        }
        write(capitalize(this_player()->GetKeyName())+"启用了oob数据监控。");
        say("你启用了oob数据监控。");
        oob = 1;
        return 1;
    }
    if(!oob){
        write("这个房间已经在屏蔽oob数据了。");
        return 1;
    }
    write(capitalize(this_player()->GetKeyName())+"禁用了oob数据监控。");
    say("你禁用了oob数据监控。");
    oob = 0;
    return 1;
}
