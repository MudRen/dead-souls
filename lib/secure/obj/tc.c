#include <lib.h>
#include NETWORK_H
inherit LIB_ITEM;

int attempting, connected, socket ;
object person, player;
string preset;
string DS_IP = "66.197.134.110 8000";

protected void create()
{
    string myname = mud_name();
    item::create();
    SetKeyName("telnet_room_client");
    SetShort( "telnet客户端" ) ;
    SetId(({"client","telnet client"}));
    SetLong( "这是一个小型口袋大小的telnet终端。\n"+
            "它似乎是专门定制用于连接Dead Souls MUD的。\n"+
            "使用'telnet'或'connect'开始。\n\n命令：\n"+
            "[connect|telnet] : 开始telnet会话。\nreset [client]"+
            " : 重置telnet客户端。\nreconnect : 重新连接到会话"+
            "（如果你断线了）\n");
    SetMass(0) ;
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
    person = 0 ;
    set_heart_beat(2);
    if(!strsrch(myname, "Dead Souls") && myname != "Dead Souls Prime"){
        DS_IP = "66.197.134.110 6666";
    }
}

void heart_beat(){
    if(!this_object() || !clonep(this_object())) return;
    if(!environment() || !living(environment()) 
            || !environment(environment())) 
        eventDestruct();
    if(this_object() && environment() && environment(environment())){
        if(!connected && base_name(environment(environment())) 
                != "/domains/default/room/telnet_room")
            eventDestruct();
    }
}

void init()
{  
    add_action( "do_connect", ({ "connect", "telnet" }) ) ;
    add_action( "do_reset", "reset" ) ;
    add_action( "do_reconnect", "reconnect" ) ;
}

void SetConnection(string str){
    if(str) preset = str;
}

int do_reconnect()
{
    if( !connected )
    {
        notify_fail( "telnet客户端未连接！\n" ) ;
        return 0 ;
    }
    write("重新连接到telnet会话。\n");
    person = this_player() ;
    input_to( "parse_comm", 0 ) ;
    return 1 ;
}

int do_reset( string args )
{
    notify_fail( "Usage: reset client\n" ) ;
    if( !args || args == "" )
    {
        return 0 ;
    }
    if( args != "client" )
    {
        return 0 ;
    }
    write("正在重置telnet客户端...\n");
    if( connected )
    {
        if( socket )
        {
            socket_close( socket ) ;
        }
    }
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
    person = 0 ;
    write("完成！\n");
    return 1 ;
}

string help()
{
    return "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
        "  用法：connect [IP地址] [端口]\n"
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
        "注意：如果你连接的是普通站点，\n"
        "      请使用telnet端口号23。\n"
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" ;
}

varargs int do_connect(string args, object whom)
{
    int new_socket, sc_result, port ;
    string error, ip_address ;

    if(preset) args = preset;
    else args = DS_IP;

    if(args != DS_IP){
        if(!this_player()) return 1;
        if(!telnet_privp(this_player())){
            this_player()->eventPrint("你不是允许使用此MUD telnet设施的用户组成员。");
            return 1;
        }
    }

    if( !args || args == "" )
    {
        notify_fail( help() ) ;
        return 0 ;
    }
    if( sscanf( args, "%s %d", ip_address, port ) != 2 )
    {
        notify_fail( help() ) ;
        return 0 ;
    }
    if( attempting )
    {
        notify_fail( "telnet连接尝试已在进行中。\n" ) ;
        return 0 ;
    }
    if( connected )
    {
        notify_fail( "已经连接...\n" ) ;
        return 0 ;
    }
    new_socket = socket_create( STREAM, "read_callback", "close_callback" ) ;
    if( new_socket < 0 )
    {
        switch( new_socket )
        {
            case EEMODENOTSUPP :
                error = "不支持的套接字模式。\n" ;
                break ;
            case EESOCKET :
                error = "创建套接字时出现问题。\n" ;
                break ;
            case EESETSOCKOPT :
                error = "setsockopt出现问题。\n" ;
                break ;
            case EENONBLOCK :
                error = "设置非阻塞模式时出现问题。\n" ;
                break ;
            case EENOSOCKS :
                error = "没有更多可用的efun套接字。\n" ;
                break ;
            case EESECURITY :
                error = "检测到安全违规尝试。\n" ;
                break ;
            default :
                error = "未知错误代码：" + new_socket + "。\n" ;
                break ;
        }
        notify_fail( "无法连接，socket_create出现问题。\n"
                "原因：" + error ) ;
        return 0 ;
    }
    sc_result = socket_connect( new_socket, ip_address + " " + port,
            "read_callback", "write_callback" ) ;
    if( sc_result != EESUCCESS )
    {
        notify_fail( "连接失败。\n" ) ;
        return 0 ;
    }
    attempting = 1 ;
    socket = new_socket ;
    person = (object)previous_object() ;
    if(!whom) player=this_player();
    else player = whom;
    input_to( "parse_comm", 0 ) ;
    return 1 ;
}

void read_callback( int fd, mixed message )
{
    player->eventPrint(message);
}

void close_callback( int fd )
{
    if( connected )
    {
        write("连接被远程主机关闭。\n");
    }
    if( attempting )
    {
        write("连接尝试失败。\n");
    }
    write("输入'dcon'以完成退出。\n");
    socket_close( fd ) ;
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
}

void write_callback( int fd )
{
    attempting = 0 ;
    connected = 1 ;
}

int parse_comm( string str )
{
    if(str=="dcon" || str=="quit")
    {
        write("你从访问另一个MUD返回了！\n");
        socket_close( socket ) ;
        attempting = 0 ;
        connected = 0 ;
        socket = 0 ;
        person = 0 ;
        this_player()->eventDescribeEnvironment();
        return 1 ;
    } else {
        if( !connected )
        {
            write("你未连接。输入'dcon'退出。\n");
            input_to( "parse_comm", 0 ) ;
            return 1 ;
        }
        if( attempting )
        {
            write("请等待，仍在尝试连接，输入'dcon'退出。\n");
            input_to( "parse_comm", 0 ) ;
            return 1 ;
        }
        socket_write( socket, str + "\n" ) ;
        input_to( "parse_comm", 0 ) ;
        return 1 ;
    }
}
