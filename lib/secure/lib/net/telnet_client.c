#include <lib.h>
#include NETWORK_H
#include <socket_err.h>
inherit LIB_ITEM;

int attempting, connected, socket ;
object person ;
object player;

protected void create()
{
    item::create();
    SetKeyName( "client" ) ;
    SetShort( "a telnet client" ) ;
    SetId(({ "telnet","terminal" })) ;
    SetLong( "这是一个小型便携式 telnet 终端。\n"
            "使用 'telnet' 或 'connect' 开始。\n\n命令：\n"
            "[connect|telnet] : 启动 telnet 会话。\nreset [client]"
            " : 重置 telnet 客户端。\nreconnect : 重新连接到会话"
            "（如果网络断线）\n");
    SetMass( 5 ) ;
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
    person = 0 ;
}

void init()
{  
    add_action( "do_connect", ({ "connect", "telnet" }) ) ;
    add_action( "do_reset", "reset" ) ;
    add_action( "do_reconnect", "reconnect" ) ;
}

int do_reconnect()
{
    if( !connected )
    {
        notify_fail( "Telnet 客户端未连接！\n" ) ;
        return 0 ;
    }
    write("正在重新连接到 telnet 会话。\n");
    person = this_player() ;
    input_to( "parse_comm", 0 ) ;
    return 1 ;
}

int do_reset( string args )
{
    notify_fail( "用法: reset client\n" ) ;
    if( !args || args == "" )
    {
        return 0 ;
    }
    if( args != "client" )
    {
        return 0 ;
    }
    write("正在重置 telnet 客户端...\n");
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
        "  用法 : connect [IP地址] [端口]\n"
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
        "注意: 如果连接到普通站点，\n"
        "      请使用 telnet 端口号 23。\n"
        "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" ;
}

int do_connect(string args)
{
    int new_socket, sc_result, port ;
    string error, ip_address ;

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
        notify_fail( "Telnet 连接尝试正在进行中。\n" ) ;
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
                error = "Socket mode not supported.\n" ;
                break ;
            case EESOCKET :
                error = "Problem creating socket.\n" ;
                break ;
            case EESETSOCKOPT :
                error = "Problem with setsockopt.\n" ;
                break ;
            case EENONBLOCK :
                error = "Problem with setting non-blocking mode.\n" ;
                break ;
            case EENOSOCKS :
                error = "No more available efun sockets.\n" ;
                break ;
            case EESECURITY :
                error = "Security violation attempted.\n" ;
                break ;
            default :
                error = "Unknown error code: " + new_socket + ".\n" ;
                break ;
        }
        notify_fail( "Unable to connect, problem with socket_create.\n"
                "Reason: " + error ) ;
        return 0 ;
    }
    sc_result = socket_connect( new_socket, ip_address + " " + port,
            "read_callback", "write_callback" ) ;
    if( sc_result != EESUCCESS )
    {
        notify_fail( "Failed to connect.\n" ) ;
        return 0 ;
    }
    attempting = 1 ;
    socket = new_socket ;
    person = (object)previous_object() ;
    player=this_player();
    write("Telnet 客户端版本 1.2\n");
    write("正在尝试连接到: " + ip_address + " " + port + "...\n随时输入 'dcon' 可中止连接。\n");
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
    write("输入 'dcon' 完成退出。\n");
    socket_close( fd ) ;
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
}

void write_callback( int fd )
{
    write("已连接...\n");
    attempting = 0 ;
    connected = 1 ;
}

int parse_comm( string str )
{
    if( str == "dcon" )
    {
        write("正在断开连接...\n");
        socket_close( socket ) ;
        attempting = 0 ;
        connected = 0 ;
        socket = 0 ;
        person = 0 ;
        return 1 ;
    } else {
        if( !connected )
        {
            write("您尚未连接。输入 \"dcon\" 停止使用客户端。\n");
            input_to( "parse_comm", 0 ) ;
            return 1 ;
        }
        if( attempting )
        {
            write("请稍候，仍在尝试连接中，"
                    "输入 'dcon' 退出。\n");
            input_to( "parse_comm", 0 ) ;
            return 1 ;
        }
        socket_write( socket, str + "\n" ) ;
        input_to( "parse_comm", 0 ) ;
        return 1 ;
    }
}

