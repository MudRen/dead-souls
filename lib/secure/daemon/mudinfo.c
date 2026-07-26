#include <daemons.h>
#include <lib.h>
#include <save.h>
#include NETWORK_H

inherit LIB_DAEMON;

mapping MudList = ([]);
mapping Unconnected = ([]);
mapping Status = ([]);
mapping Confirmed = ([]);
int attempting, connected, socket ;
object person, player;
string preset;
int age, probing;
string *queue = ({});
nosave string SaveFile;

int SetQueue(string str){
    if(file_exists(str)){
        foreach(string line in explode(read_file(str),"\n")){
            queue += ({ trim(line) });
        }
    }
    return 1;
}

int SetProbing(int x){
    if(x) probing = 1;
    else probing = 0;
    this_object()->PrintUnconnectedInfo();
    return probing;
}

string GetMudName(string mud){
    if( MudList[mud] ) return mud;
    foreach(string name in keys(MudList)){
        if(lower_case(name) == lower_case(mud)) return name;
    }
    return 0;
}

int PrintMudInfo(string str){
    mixed *info;
    mixed *list;
    mapping borg;
    string mud, tempy;
    int all = 0;
    if(!MudList && unguarded((: file_exists(SaveFile) :))){
        RestoreObject(SaveFile, 1);     
    }
    if(!MudList) MudList = ([]);
    if(!str || str == "all"){
        write("MUD总数: "+sizeof(MudList));
        write("MUD列表: "+implode(sort_array(keys(MudList), 1),", "));
        return 1;
    }

    list = INTERMUD_D->GetMudList();
    if(mapp(list)){
        foreach(mixed key, mixed val in list){
            MudList[key] = val;
        }
    }

    if(sizeof(str) && sizeof(tempy = INTERMUD_D->GetMudName(str) )) str = tempy;
    if(!tempy){
        if(MudList) tempy = GetMudName(str);
    }
    if(!tempy){
        write("未找到MUD。");
        return 1;
    }
    info = INTERMUD_D->GetMudList()[tempy];
    if(!info) info = MudList[tempy];
    if(!info){
        write("没有关于 "+tempy+" 的信息");
        return 1;
    }
    write("MUD名称: "+tempy);
    write("状态: "+(info[0] < 0 ? "在线" : "离线"));
    write("IP地址: "+info[1]);
    write("端口: "+info[2]);
    write("IMUD带外(TCP OOB)端口: "+info[3]);
    write("IMUD UDP端口(已废弃): "+info[4]);
    write("MUD库: "+info[5]);
    write("基础MUD库: "+info[6]);
    write("驱动: "+info[7]);
    write("MUD类型: "+info[8]);
    write("开放状态: "+info[9]);
    write("管理员邮箱: "+info[10]);
    if(sizeof(info[11])){
        string tmp = "服务: ";
        foreach(mixed key, mixed val in info[11]){
            if(val) tmp += key+" ";
        }
        write(tmp+"\n");
    }
    if(sizeof(info[12])){
        write("额外信息\n---------- ");
        foreach(mixed key, mixed val in info[12]){
            write(identify(key)+": "+identify(val));
        }
    }
    return 1;
}

int ReceiveMudInfo(string str,mapping info){
    if(!MudList[str]) MudList[str] = info;
    return sizeof(MudList[str]);
}

void GenerateConnectionPage(){
    string ret = "<html>";
    foreach(mixed key in sort_array(keys(MudList),1)){
        mapping val = MudList[key];
        if(val[0] < 0){
            ret += key + " ";
            ret += val[6] + " ";
            ret += val[1]+" "+val[2]+"<br>";
        }
    }
    write_file("/www/mudlist.html",ret,1);
}

void create(){
    mapping list = INTERMUD_D->GetMudList();
    SaveFile = save_file(SAVE_MUDINFO);
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
    person = 0 ;
    set_heart_beat(1);
    if(unguarded((: file_exists(SaveFile) :))){
        RestoreObject(SaveFile);
    }
    if(mapp(list)){
        foreach(mixed key, mixed val in list){
            if(!MudList[key]) MudList[key] = val;
        }
    }
    SaveObject(SaveFile);
}

int PrintUnconnectedInfo(){
    int rebuild;
    if(!Unconnected) Unconnected = ([]);
    if(!sizeof(Unconnected)) rebuild = 1;
    foreach(mixed key, mixed val in MudList){
        if(val[0] != -1){
            if(this_player()) write(key+": telnet "+val[1]+" "+val[2]);
            if(rebuild) Unconnected[key] = ([ "ip": val[1], "port" : val[2] ]);
        }
    }
    return 1;
}

void heart_beat(){
    if(!this_object()) return;
    if(time() > age + 2){
        this_object()->do_reset();
    }
    if(sizeof(queue)){
        this_object()->do_connect(queue[0], queue[0]);
        if(sizeof(queue) > 1) queue = queue[1..];
        else queue = ({});
    }
    else if(probing && !connected && !attempting && sizeof(Unconnected)){
        string target = keys(Unconnected)[0]; 
        this_object()->do_connect(Unconnected[target]["ip"]+
                " "+Unconnected[target]["port"], target);
        map_delete(Unconnected, target);
    }
}

void SetConnection(string str){
    if(str) preset = str;
}

int do_reconnect()
{
    if( !connected )
    {
        notify_fail( "Telnet客户端未连接！\n" ) ;
        return 0 ;
    }
    write("重新连接Telnet会话。\n");
    person = this_player() ;
    input_to( "parse_comm", 0 ) ;
    return 1 ;
}

int do_reset( string args )
{
    if( socket ){
        socket_close( socket ) ;
    }
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
    return 1 ;
}

varargs int do_connect(string args, string mud){
    int new_socket, sc_result, port ;
    string error, ip_address ;

    if(preset) args = preset;

    if( sscanf( args, "%s %d", ip_address, port ) != 2 ){
        return 0 ;
    }
    if( attempting || connected ){
        return 0 ;
    }
    new_socket = socket_create( STREAM, "read_callback", "close_callback" ) ;
    if( new_socket < 0 ){
        switch( new_socket ){
            case EEMODENOTSUPP :
                error = "不支持的套接字模式。\n" ;
                break ;
            case EESOCKET :
                error = "创建套接字出错。\n" ;
                break ;
            case EESETSOCKOPT :
                error = "设置套接字选项出错。\n" ;
                break ;
            case EENONBLOCK :
                error = "设置非阻塞模式出错。\n" ;
                break ;
            case EENOSOCKS :
                error = "没有可用的efun套接字。\n" ;
                break ;
            case EESECURITY :
                error = "安全违规尝试。\n" ;
                break ;
            default :
                error = "未知错误代码: " + new_socket + "。\n" ;
                break ;
        }
        return 0 ;
    }
    sc_result = socket_connect( new_socket, ip_address + " " + port,
            "read_callback", "write_callback" ) ;
    if( sc_result != EESUCCESS ){
        return 0 ;
    }
    attempting = 1 ;
    socket = new_socket ;
    age = time();
    if(!Status) Status = ([]);
    Status[new_socket] = mud;
    return 1 ;
}

void read_callback( int fd, mixed message ){
    if(!Confirmed) Confirmed = ([]);
    if(!Confirmed[Status[fd]]) Confirmed[Status[fd]] = (["banner" : message, ]);
    else Confirmed[Status[fd]]["banner"] +=  message;
}

void close_callback( int fd ){
    socket_close( fd ) ;
    attempting = 0 ;
    connected = 0 ;
    socket = 0 ;
}

void write_callback( int fd ){
    attempting = 0 ;
    connected = 1 ;
}

int parse_comm( string str ){
    if(str=="dcon" || str=="quit"){
        socket_close( socket ) ;
        attempting = 0 ;
        connected = 0 ;
        socket = 0 ;
        person = 0 ;
        return 1 ;
    } 
    else {
        if( !connected ){
            return 1 ;
        }
        if( attempting ){
            return 1 ;
        }
        socket_write( socket, str + "\n" ) ;
        return 1 ;
    }
}
